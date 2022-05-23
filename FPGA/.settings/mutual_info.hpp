/******************************************
 *MIT License
 *
 *Copyright (c) [2020] [Davide Conficconi, Eleonora D'Arnese, Emanuele Del Sozzo, Marco Domenico Santambrogio]
 *
 *Permission is hereby granted, free of charge, to any person obtaining a copy
 *of this software and associated documentation files (the "Software"), to deal
 *in the Software without restriction, including without limitation the rights
 *to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *copies of the Software, and to permit persons to whom the Software is
 *furnished to do so, subject to the following conditions:
 *
 *The above copyright notice and this permission notice shall be included in all
 *copies or substantial portions of the Software.
 *
 *THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *SOFTWARE.
 */
 /***************************************************************
 *
 * High-Level-Synthesis header file for Mutual Information computation
 *
 ****************************************************************/
 #ifndef MUTUAL_INF_H
 #define MUTUAL_INF_H
 #include "ap_int.h"

 typedef float data_t;
 #define DATA_T_BITWIDTH 32
 typedef ap_uint<8> MY_PIXEL;
 //0

 #define TWO_FLOAT 2.0f
 #define OUT_BUFF_SIZE 1

 #define ENTROPY_THRESH 0.000000000000001
 #define ENTROPY_FLT_THRESH 0.000000000001
 #define ENTROPY_REF_THRESH 0.000000000001

 /************/

 /*********** SIM used values **********/
 #define DIMENSION 512
 //1
 /*********** End **********/

 #define MYROWS DIMENSION // Y
 #define MYCOLS DIMENSION

 /*********** SIM used values **********/
 #define MAX_RANGE (int)(MAX_FREQUENCY - 1)
 /*********** End **********/

 /*
  Joint Histogram computations
 */

 #define HIST_PE 1
 //2
 #define UNPACK_DATA_BITWIDTH 8
 //0
 #define UNPACK_DATA_TYPE ap_uint<UNPACK_DATA_BITWIDTH>

 #define INPUT_DATA_BITWIDTH (HIST_PE*UNPACK_DATA_BITWIDTH)
 #define INPUT_DATA_TYPE ap_uint<INPUT_DATA_BITWIDTH>

 #define NUM_INPUT_DATA (DIMENSION*DIMENSION/(HIST_PE))

 #define WRAPPER_HIST2(num) wrapper_joint_histogram_##num
 #define WRAPPER_HIST(num) WRAPPER_HIST2(num)

 #define WRAPPER_ENTROPY2(num) wrapper_entropy_##num
 #define WRAPPER_ENTROPY(num) WRAPPER_ENTROPY2(num)

 #define J_HISTO_ROWS 256
 //3
 #define J_HISTO_COLS J_HISTO_ROWS
 #define MIN_HIST_BITS 19
 //4
 //#define MIN_J_HISTO_BITS (int)(std::ceil(std::log2(MYROWS*MYCOLS)))
 // TODO overflow non contemplato :D, sarebbe + 1
 #define MIN_HIST_PE_BITS (MIN_HIST_BITS - 1)
 //5
 //#define MIN_HISTO_PE_BITS (int)(std::ceil(std::log2(ROW_PE_KRNL*COLS_PE_KRNL)))
 //MIN_HIST_BITS - log2(HIST_PE)


 typedef ap_uint<MIN_HIST_BITS> MinHistBits_t;
 typedef ap_uint<MIN_HIST_PE_BITS> MinHistPEBits_t;


 #define ENTROPY_PE 1
 //6
 const unsigned int ENTROPY_PE_CONST = ENTROPY_PE;

 #define PACKED_HIST_PE_DATA_BITWIDTH (MIN_HIST_PE_BITS*ENTROPY_PE)
 #define PACKED_HIST_PE_DATA_TYPE ap_uint<PACKED_HIST_PE_DATA_BITWIDTH>

 #define PACKED_HIST_DATA_BITWIDTH (MIN_HIST_BITS*ENTROPY_PE)
 #define PACKED_HIST_DATA_TYPE ap_uint<PACKED_HIST_DATA_BITWIDTH>

 //#define PACKED_DATA_T_DATA_BITWIDTH (INNER_ENTROPY_TYPE_BITWIDTH*ENTROPY_PE)
 //#define PACKED_DATA_T_DATA_TYPE ap_uint<PACKED_DATA_T_DATA_BITWIDTH>

 #define UINT_OUT_ENTROPY_TYPE_BITWIDTH 23
 //7
 // MAX std::ceil(std::log2( log2(MYROWS*MYCOLS) * (MYROWS*MYCOLS) )) + 1
 #define UINT_OUT_ENTROPY_TYPE ap_uint<UINT_OUT_ENTROPY_TYPE_BITWIDTH>

 #define FIXED_BITWIDTH 42
 #define FIXED_INT_BITWIDTH UINT_OUT_ENTROPY_TYPE_BITWIDTH
 //#define FIXED ap_ufixed<42, 23>
 //8
 #ifndef FIXED
     #define ENTROPY_TYPE data_t
     #define OUT_ENTROPY_TYPE data_t
 #else
     #define ENTROPY_TYPE FIXED
     #define OUT_ENTROPY_TYPE UINT_OUT_ENTROPY_TYPE
 #endif


 #define ANOTHER_DIMENSION J_HISTO_ROWS // should be equal to j_histo_rows


 //UNIFORM QUANTIZATION
 #define INTERVAL_NUMBER 256 // L, amount of levels we want for the binning process, thus at the output
 //9
 #define MAX_FREQUENCY 256 // or 255? the maximum number of levels at the input stage
 //10
#define MINIMUM_FREQUENCY 0
 #define INTERVAL_LENGTH ( (MAX_FREQUENCY - MINIMUM_FREQUENCY) / INTERVAL_NUMBER ) // Q = (fmax - fmin )/L
 #define INDEX_QUANTIZED(i) (i/INTERVAL_LENGTH) // Qy(i) =  f - fmin / Q

 /*****************/
 const ENTROPY_TYPE scale_factor = 3.814697265625e-06f;
//11
 //constexpr float scale_factor = 1.0f /(DIMENSION*DIMENSION);

 #ifndef CACHING
     extern  void mutual_information_master(INPUT_DATA_TYPE * input_img, INPUT_DATA_TYPE * input_ref, data_t * mutual_info);
 #else
     extern  void mutual_information_master(INPUT_DATA_TYPE * input_img,  data_t * mutual_info, unsigned int functionality, int* status);
 #endif

 //12
 #define ACC_SIZE 16
 // 13


#endif
