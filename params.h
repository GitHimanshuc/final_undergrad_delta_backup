// //This file lists various parameters that can be quickly changed for various runs
// #ifndef guard_params

// #define guard_params

// #define datdir "/home/himanshu/Desktop/final-undergraduate_project/data/" //Directory where data is located

// // #define deltaT 0.02     //Time step (ms)

// #define deltaT 0.02 //Time step (ms)
// // #define deltaX 0.025   //Time step (ms)
// #define deltaX 0.0025     //space step (cm)
// //#define numProcs 4
// const int interval = 600; //Print to file every T_NOUT time-steps
// // const int interval=6000;      //Print to file every T_NOUT time-steps
// #define maxtime 300000.0 //maxtime is total no. of iterations = T_TOTAL/dt
// // #define maxtime 3000000.  //maxtime is total no. of iterations = T_TOTAL/dt
// #define stimtime 10000.0 //Duration for which stimulus is applied
// // #define stimtime 80.0   //Duration for which stimulus is applied
// #define Istim -25.0           //-25; //Amplitude of stimulus applied
// #define secondstimstart 5000000. //second stimulus is applied at this time(ms)
// #define n_mean 1.0           //mean value of no. of fibroblasts attached
// #define DcoeffOrig 0.00006   //Value of diffusion coefficient

// // const int spacex= 128;   //Spacex is number of points in x direction. This is to be divided among processors
// const int spacex = 40; //Spacex is number of points in x direction. This is to be divided among processors
// // const int space=  128;   //Space is number of points along y direction, this remains the same for all processors
// const int space = 24; //Space is number of points along y direction, this remains the same for all processors

// const int run_min = 1; //initial index of parameter run
// const int run_max = 1; //maximum index of parameter run

// #endif

//This file lists various parameters that can be quickly changed for various runs

#define datdir "/localscratch/ughima/32procs/data/"


// #define deltaT 0.02     //Time step (ms)
#define deltaT 0.02 //Time step (ms)
// #define deltaX 0.025   //Time step (ms)
#define deltaX 0.025     //space step (cm)
const int interval = 100; //Print to file every T_NOUT time-steps
// const int interval=6000;      //Print to file every T_NOUT time-steps
// #define maxtime 300000.0 //maxtime is total no. of iterations = T_TOTAL/dt
#define maxtime 100000.0 //maxtime is total no. of iterations = T_TOTAL/dt
#define stimtime 80.0 //Duration for which stimulus is applied
// #define stimtime 80.0   //Duration for which stimulus is applied
#define Istim -25.0          //-25; //Amplitude of stimulus applied
#define secondstimstart 5000000.0 //second stimulus is applied at this time(ms)
#define n_mean 1.0          //mean value of no. of fibroblasts attached
#define DcoeffOrig 0.0006   //Value of diffusion coefficient
// #define DcoeffOrig 0.00006   //Value of diffusion coefficient

// const int spacex= 128;   //Spacex is number of points in x direction. This is to be divided among processors
const int spacex = 64; //Spacex is number of points in x direction. This is to be divided among processors
// const int space=  128;   //Space is number of points along y direction, this remains the same for all processors
const int space = 64; //Space is number of points along y direction, this remains the same for all processors

const int run_min = 1; //initial index of parameter run
const int run_max = 14; //maximum index of parameter run
            
