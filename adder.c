#include"wire.h"
#include"gate.h"
#include"task.h"
#include"adder.h"
#include<math.h>

H_ADDER_t* new_half_adder(W* input1, W* input2, \
		          W* sum, W* carry){
	H_ADDER_t* half_adder = (H_ADDER_t*)\
				malloc(sizeof(H_ADDER_t));
	if(!half_adder){
		perror("create half adder failed!");
		exit(-1);
	}
	half_adder->A_in = input1;
	half_adder->B_in = input2;
	half_adder->Sum = sum;
	half_adder->Carry_out = carry;
	half_adder->xor_gate = mk_xor(input1, input2, sum);
	half_adder->and_gate = mk_and(input1, input2, carry);

	return half_adder;
}

F_ADDER_t* new_full_adder(W* input1, W* input2, W* sum, \
		          W* carry_in, W* carry_out){
	F_ADDER_t* full_adder = (F_ADDER_t*)\
				malloc(sizeof(F_ADDER_t));
	if(!full_adder){
		perror("Create full adder failed!");
		exit(-1);
	}
	W* w_1 = mk_wire();
	W* w_2 = mk_wire();
	W* w_3 = mk_wire();
	full_adder -> w_1 = w_1;
	full_adder -> w_2 = w_2;
	full_adder -> w_3 = w_3;

	full_adder -> A_in = input1;
	full_adder -> B_in = input2;
	full_adder -> Sum = sum;
	full_adder -> Carry_in = carry_in;
	full_adder -> Carry_out = carry_out;
	full_adder -> input_add = new_half_adder(\
			input1, input2, w_1, w_2);
	full_adder -> carry_add = new_half_adder(\
			carry_in, w_1, sum, w_3);
	full_adder -> Carry_comp = mk_or(\
			w_3, w_2, carry_out);

	return full_adder;
}

BUF_t* new_buffer(int size){
	int i;
	BUF_t* buffer = (BUF_t*)malloc(sizeof(BUF_t));
	buffer->size = size;
	W** _buffer = (W**)malloc(size*sizeof(W*));
	if(!(buffer && _buffer)){
		perror("create buffer failed!");
		exit(-1);
	}
	for(i=0; i<size; i++){
		_buffer[i] = mk_wire();
	}
	buffer->_buf = _buffer;
	return buffer;
}

void set_new_buffer(TASK_q* queue, BUF_t* buffer, \
		int* nums, int size){
	int i;
	if(size){
		buffer->size = size;
	}
	W** _buf = buffer->_buf;
	for(i=0; i<buffer->size; i++){
		set_wire(queue, _buf[i], nums[i]);
	}
}

void read_new_buffer(BUF_t* buffer, int size){
	int i;
	W** buf = buffer->_buf;
	for(i=0; i<size; i++){
		printf("%d ", get_status(buf[i]));
	}
	printf("\n");
}


/************************************************************************
 * 8BIT ADDER
 *                 A Input                      B Input         Carry In
 *              | | | | | | | |              | | | | | | | |        |
 *          +---------------------------------------------------+   |
 *          |     A7.....A1                     B7.....B1       |   |
 *     +----+                                                   +---+
 *     |    |                   S7.....S0                       |
 *     |    +---------------------------------------------------+
 *  Carry Out                | | | | | | | |
 *                               S Output
 **********************************************************************/

/**************************************************************************
 * 32BIT ADDER
 *          A_In       B_In                  A_In        B_In
 *           ||        ||                     ||          ||
 *           \/        \/                     \/          \/  Carry In
 *       +--------------------+           +---------------------+ |
 *       | A31.A24   B31.B24  |      C_out|  A7..A0     B7..B0  | |
 *     +-+                    +---....----+                     +-+
 *     | |      S31.S24       |C_in       |        S7..S0       |
 *     | +--------------------+           +---------------------+
 * Carry Out       ||                                ||
 *                 \/                                \/
 *               S_Out                              S_Out
 *************************************************************************/

/**********************************************************************
 * ADDER
 *                                                                         
 *            A INPUT                   B INPUT              CARRY IN
 *              ||                        ||                     |
 *              ||                        \/                     |
 *              ||                   +-----------+               |
 *              ||                   |  B31..B0  |               |
 *              ||                   |           +---------------+
 *              ||                   |  C31..C0  |               |
 *              ||                   +-----------+               |
 *              ||                        ||                     |
 *              \/                        \/                     |
 *        +--------------------------------------+               |
 *        | A31..A0                    C31..C0   |               |
 *    +---+                                      +---------------+
 *    |   |             S31..S0                  |
 *    |   +--------------------------------------+
 *    |  CARRY IN         ||
 *    |     |             \/
 *   \ /   \ /          OUTPUT 
 *   +--------+
 *   |  xor   |
 *   +--------+
 *      ||
 *      \/
 *    overflow/
 *    underflow
 **********************************************************************/

ADDER_t* new_adder(BUF_t* A, BUF_t* B, BUF_t* S, \
		W* carry, W* flow, int size){
	int i;
	W** a = A->_buf;
	W** s = S->_buf;
	W* carry_out = mk_wire();
	BUF_t* one_complement_buffer = new_buffer(size);
	W** carry_trans = (W**)malloc((size-1)*sizeof(W*));
	if(!carry_trans){
		perror("failed when create carry_trans \
				for new adder!");
		exit(-1);
	}
	for(i=0; i<size-1; i++){
		carry_trans[i] = mk_wire();
	}

	ADDER_t* adder = (ADDER_t*)malloc(sizeof(ADDER_t));
	if(!adder){
		perror("create new adder failed!");
		exit(-1);
	}
	adder -> size = size;
	adder -> carry_trans = carry_trans;
	adder -> flow = flow;
	adder -> add_sub_switch = carry;
	adder -> A_buffer = A;
	adder -> B_buffer = B;
	adder -> OUT_buffer = S;
	adder -> Complement = new_complement(B, \
			one_complement_buffer, carry, size);

	F_ADDER_t** _full_adders = (F_ADDER_t**)\
			    malloc(size*sizeof(F_ADDER_t*));
	if(!_full_adders){
		perror("failed when create full adders \
				for new adder!");
		exit(-1);
	}
	_full_adders[0] = new_full_adder(a[0], \
			(one_complement_buffer->_buf)[0], \
			 s[0], carry, carry_trans[0]);
	for(i=1; i<size-1; i++){
		_full_adders[i] = new_full_adder(a[i], \
				(one_complement_buffer->_buf)[i], \
				s[i], carry_trans[i-1], \
				carry_trans[i]);
	}
	_full_adders[size-1] = new_full_adder(a[size-1], \
			(one_complement_buffer->_buf)[size-1], \
			s[size-1], carry_trans[size-2], \
			carry_out);
	adder -> F_adders = _full_adders;

	adder -> flow_comp = mk_xor(carry_out, carry, flow);

	return adder;
}

COMPLEMENT_t* new_complement( BUF_t* in, BUF_t* out, \
		W* _switch, int size){
	int i;

	W** _buf_in = in->_buf;
	W** _buf_out = out->_buf;

	G** gates = (G**)malloc(size*sizeof(G*));
	if(!gates){
		perror("failed create for complement!");
		exit(-1);
	}

	COMPLEMENT_t* _complement = (COMPLEMENT_t*)\
				     malloc(sizeof(COMPLEMENT_t));
	if(!complement){
		perror("create complement failed!");
		exit(-1);
	}
	_complement->size = size;
	_complement -> _switch = _switch;
	_complement -> in = in;
	_complement -> out = out;
	_complement -> _xor_gates = gates;

	for(i=0; i<size; i++){
		gates[i] = mk_xor(_buf_in[i], _switch, _buf_out[i]);
	}

	return _complement;
}

void copy_new_buffer(TASK_q* queue, BUF_t* src, BUF_t* des, int size){
	int i;
	W** src_buf = src->_buf;
	W** des_buf = des->_buf;

	for(i=0; i<size; i++){
		set_wire(queue, des_buf[i], get_status(src_buf[i]));
	}
}

void zero_new_buffer(BUF_t* buffer){
	int i;
	W** _buf = buffer->_buf;
	for(i=0; i<buffer->size; i++){
		_buf[i]->status = 0;
	}
}

int buf_to_signed_i(BUF_t* buffer){
	int i, sign, total = 0;
	W** _buf = buffer->_buf;
	sign = get_status(_buf[31]);
	for(i=0; i<31; i++){
		total += (get_status(_buf[i]) * pow(2,i));
	}
	total += (-1*sign)*pow(2, 31);

	return total;
}
