#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <string.h>
#include <time.h>
// #define datdir "/home/ug/15/ughima/code/new_2d_code/data/"
// #define datdir "/home/himanshu/Desktop/final_year_now/data/"





char name[200];
char RUN[50];


#include "params.h"
#include "random_number_generator.h"
#include "functions.h"


int run;


int main(int argc, char *argv[])
{

    double starttime;
    double endtime;



    int myStarti;
    int myEndi;
    int mypoints;
    int leftProc;
    int rightProc;
    int myrank;
    int numProcs = 32;



    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &numProcs);

    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);

    char procname[numProcs];
    int namelen;

    starttime = MPI_Wtime();


    mypoints = spacex / numProcs;

    myStarti = myrank * mypoints + 1;

    myEndi = myStarti + mypoints - 1;


    char filename[numProcs];

    int i = 0;
    int j = 0;
    int k = 0;
    int iter = 0;



    char     temp_string[256];    // Temporary string variable

    char filenumber[5];
    FILE *Vout[numProcs],*VoutM[numProcs], *V_out[numProcs], *V_in, *Tser[numProcs], *Nout[numProcs];
    FILE *V_f_outnum[numProcs], *V_f_in;
    FILE *F_n = NULL;


    double ElecA1;

    printf("%s\n", "Starting memory alloaction.");

    double t = 0.0;
    double dt = 0.0;
    double del_x = 0.0;
    double D[mypoints + 2][space + 2];





    double I_stim[mypoints + 2][space + 2];
    double v[mypoints + 2][space + 2];
    double V1[mypoints + 2][space + 2];
    double v_f[mypoints + 2][space + 2];
    double cai[mypoints + 2][space + 2];
    int n[mypoints + 2][space + 2];
    // double n[mypoints + 2][space + 2];
    double G_j[mypoints + 2][space + 2];

    double E_f = -25.;
    double C_f = 80.;
    double C_m = 120.;
    double G_f = 1.;

    double ik[mypoints + 2][space + 2];
    double it[mypoints + 2][space + 2];
    double jt[mypoints + 2][space + 2];
    double Ft[mypoints + 2][space + 2];

   
    double ki = 140.0;
    double nai = 4.0;
    double cli = 46.0;
    double ko = 6.0;
    double cao = 2.5;
    double nao = 130.0;
    double clo = 130.0;
    double mgo = 0.5;

    double buff = 0.015;
    double AV = 4.0;


    double w[mypoints + 2][space + 2];
    double Fmax = 3.0;
    double FKm = 161.301;
    double Fn = 3.60205;
    double wss = 0.;
    double wtc = 0.;



    double m[mypoints + 2][space + 2];
    double h[mypoints + 2][space + 2];
    double gna = 0.12;
    double mss = 0.;
    double hss = 0.;
    double mtc = 0.;
    double htc = 0.;
    double ena = 0.;
    double ina[mypoints + 2][space + 2];



    double d[mypoints + 2][space + 2];
    double f1[mypoints + 2][space + 2];
    double f2[mypoints + 2][space + 2];
    double gcal = 0.6;
    double ecal = 45.0;
    double kmca = 0.001;
    double fca = 0.;
    double dss = 0.;
    double f1ss = 0.;
    double f2ss = 0.;
    double dtc = 0.;
    double f1tc = 0.;
    double f2tc = 0.;
    double ical[mypoints + 2][space + 2];



    double b[mypoints + 2][space + 2];
    double g[mypoints + 2][space + 2];
    double gcat = 0.058;
    double ecat = 42.0;
    double bss = 0.;
    double gss = 0.;
    double btc = 0.;
    double gtc = 0.;
    double icat[mypoints + 2][space + 2];



    double gk = 0.8;
    double gkca = 0.8;



    double gb = 0.004;
    double ek = 0.;
    double ib[mypoints + 2][space + 2];



    double q[mypoints + 2][space + 2];
    double r1[mypoints + 2][space + 2];
    double r2[mypoints + 2][space + 2];
    double gk1 = 0.65;
    double qss = 0.;
    double r1ss = 0.;
    double r2ss = 0.;
    double qtc = 0.;
    double r1tc = 0.;
    double r2tc = 0.;
    double ik1[mypoints + 2][space + 2];



    double p[mypoints + 2][space + 2];
    double k1[mypoints + 2][space + 2];
    double k2[mypoints + 2][space + 2];
    double gk2 = 0.04;
    double pss = 0.;
    double k1ss = 0.;
    double k2ss = 0.;
    double ptc = 0.;
    double k1tc = 0.;
    double k2tc = 0.;
    double ik2[mypoints + 2][space + 2];



    double xa[mypoints + 2][space + 2];
    double gbka = 0.2;
    double xass_z = 0.;
    double xass_vh = 0.;
    double xass = 0.;
    double xatc = 0.;
    double BKa[mypoints + 2][space + 2];



    double xab[mypoints + 2][space + 2];
    double gbkab = 0.1;
    double xabss_z = 0.;
    double xabss_vh = 0.;
    double xabss = 0.;
    double xabtc = 0.;
    double BKab[mypoints + 2][space + 2];



    double s[mypoints + 2][space + 2];
    double x[mypoints + 2][space + 2];
    double gka = 0.2;
    double sss = 0.;
    double xss = 0.;
    double stc = 0.;
    double xtc = 0.;
    double ika[mypoints + 2][space + 2];



    double y[mypoints + 2][space + 2];
    double gh = 0.0542;
    double PK = 1.0;
    double PNa = 0.35;
    double yss = 0.;
    double ya = 0.;
    double yb = 0.;
    double ytc = 0.;
    double eh = 0.;
    double ih[mypoints + 2][space + 2];



    double c[mypoints + 2][space + 2];
    double gcl = 0.1875;
    double K1cl = 0.;
    double K2cl = 0.;
    double css = 0.;
    double ctc = 0.;
    double ecl = 0.;
    double icl[mypoints + 2][space + 2];



    double gns = 0.0123;
    double gl = 0.0;
    double PnsK = 1.3;
    double PnsNa = 0.9;
    double PnsCa = 0.89;
    double PnsCs = 1.0;
    double gnsCa = 0.5;
    double gnsNa = 1.0;
    double gnsK = 1.19;
    double gnsCs = 1.6;
    double fmg = 0.;
    double enscc = 0.;
    double insca = 0.;
    double insna = 0.;
    double insk = 0.;
    double il = 0.;
    double inscc[mypoints + 2][space + 2];



    double ginak = 1.7;
    double nakKmko = 2.0;
    double nakKmnai = 22.0;
    double fnak = 0.;
    double knak = 0.;
    double nnak = 0.;
    double inak[mypoints + 2][space + 2];



    double Jnaca = 3.5e-6;
    double Kmallo = 0.0003;
    double nallo = 4;
    double ksat = 0.27;
    double xgamma = 0.35;
    double Kmnai = 30.0;
    double Kmcai = 0.007;
    double Kmnao = 87.5;
    double Kmcao = 1.3;
    double f1naca = 0.;
    double f2naca = 0.;
    double fallo = 0.;
    double naca_Eup = 0.;
    double naca_Ed1 = 0.;
    double naca_Ed2 = 0.;
    double naca_Ed3 = 0.;
    double jnaca = 0.;
    double inaca[mypoints + 2][space + 2];




    double Jpmca = 3.5e-7;
    double Kmpmca = 0.0005;
    double npmca = 2;
    double jpmca = 0;

    printf("%s\n", "No errors in declaration.");



    leftProc = myrank - 1;
    rightProc = myrank + 1;
    if (leftProc < 0)
        leftProc = MPI_PROC_NULL;
    if (rightProc >= numProcs)
        rightProc = MPI_PROC_NULL;


    char   mkcmd[256];    // Temporary string variable


    for (run = run_min; run <= run_max; run++)
    {
        dt = deltaT;
        del_x = deltaX;
        t = 0;

        printf("Reached run loop%d.\n",run);
        sprintf(mkcmd, "mkdir -p %srun%d", datdir,run);
        system(mkcmd);

        generate_poisson(n_mean, mypoints * space, myrank, myrank + 1, run);
        strcpy(name, datdir);
        sprintf(RUN, "run%d/", run);
        strcat(name, RUN);
        strcat(name, "random");
        sprintf(filenumber, "%04d", myrank);
        strcat(name, filenumber);
        strcat(name, ".dbl");
        F_n = fopen(name, "rb");
        if (F_n == NULL)
        {
            printf("ERROR in reading input file (%s) \n", name);
            exit(1);
        }




        for (i = 1; i <= mypoints; i++)
        {
            for (j = 1; j <= space; j++)
            {
                v[i][j] = -53.90915441282156;
                V1[i][j] = v[i][j];
                v_f[i][j] = E_f;
                cai[i][j] = 0.0001161881607214449;




                // n[i][j] = n_mean;
                // n[i][j] = (j / (float)space * run*0.3);

                // if ( (i+j)%7==0)
                // {
                //     n[i][j] = 3.0;
                // }
                // else
                // {
                //     n[i][j] = 0.0;
                // }
                // n[i][j] = 1.5;
                // if (myrank <25 && myrank > 7 && j < space *25/32 && j > space *7/32)
                // {
                //     n[i][j] = 0.0;
                // }
                // if (myrank <19 && myrank > 13 && j < space *19/32 && j > space *13/32)
                // {
                //     n[i][j] = 1.5;
                // }

                // if (myrank == 15 && j>space*4.0/10 && j< space*6.0/10)
                // {
                //     n[i][j] = 3.0;

                // }
                // else
                // {
                //     n[i][j] =0.0;
                // }





                // if (j<space/2-25)
                // {
                //     n[i][j] = 0.0/4;

                // }
                // else if (j<space/2-10)
                // {
                //     n[i][j] = 1.0/4;
                // }
                // else if (j<space/2-5)
                // {
                //     n[i][j] = 2.0/4;
                // }
                // else if (j<space/2)
                // {
                //     n[i][j] = 3.0/4;
                // }
                // else
                // {
                //     n[i][j] = 4.0/4;
                // }
                fread(&n[i][j], sizeof(int), 1, F_n);
                // fread(&n[i][j], sizeof(float), 1, F_n);
                G_j[i][j] = 0.1*run;
                m[i][j] = 0.1253518889572223;
                h[i][j] = 0.404599170710196;
                b[i][j] = 0.508117603077852;
                g[i][j] = 0.03582573962705717;
                d[i][j] = 0.01036961357784695;
                f1[i][j] = 0.9065941499695301;
                f2[i][j] = 0.9065967263076083;
                q[i][j] = 0.2060363247740295;
                r1[i][j] = 0.1922244113609531;
                r2[i][j] = 0.1932803618375963;
                p[i][j] = 0.1174074734567931;
                k1[i][j] = 0.9968385770271651;
                k2[i][j] = 0.9968408069904307;
                xa[i][j] = 0.0003569126518797985;
                xab[i][j] = 0.002220456569762898;
                s[i][j] = 0.0307583106982354;
                x[i][j] = 0.08785242843398365;
                y[i][j] = 0.002604864867063448;
                c[i][j] = 0.0003764413740731269;
                w[i][j] = 0.2345238135343783;
                D[i][j] = DcoeffOrig;
            }
        }




        strcpy(filename, datdir);

        sprintf(RUN, "run%d/", run);
        strcat(filename, RUN);
        sprintf(name, "myo1p%02d.dat", myrank);
        strcat(filename, name);
        Vout[myrank] = fopen(filename, "w");




        strcpy(filename, datdir);
        sprintf(RUN, "run%d/", run);
        strcat(filename, RUN);
        sprintf(name, "MAT%d.dat", myrank);
        strcat(filename, name);
        VoutM[myrank] = fopen(filename, "w");


        strcpy(filename, datdir);
        sprintf(RUN, "run%d/", run);
        strcat(filename, RUN);
        sprintf(name, "N_data%d.dat", myrank);
        strcat(filename, name);
        Nout[myrank] = fopen(filename, "w");



        strcpy(filename, datdir);

        sprintf(RUN, "run%d/", run);
        strcat(filename, RUN);
        sprintf(name, "TserE%02d.dat", myrank);
        strcat(filename, name);
        Tser[myrank] = fopen(filename, "w");



        // This is just a random variable to be used for printing progress
        int per_com;
        per_com = (int)(maxtime/100);
       
        // Another cosmetic thing for measuring time left
        clock_t start ,now;
        start = clock()/(CLOCKS_PER_SEC);

        for (iter = 1; iter <= maxtime; iter++)
        {

            if(myrank == 0){

                if( iter % per_com == 0){
                    now = clock()/(CLOCKS_PER_SEC);
                    printf("%.2f percent done   -----  ", iter*100/maxtime);
                    printf("%.2f / %.2f minutes\n", (double)(now - start)/60,(double)((now - start)*maxtime/iter)/60);
                }
            }


            t = t + dt;


            for (i = 1; i < (mypoints + 1); i++)
            {
                v[i][0] = v[i][2];
                v[i][space + 1] = v[i][space - 1];
            }

            if (myrank == 0)
            {
                for (j = 1; j <= space; j++)
                    v[0][j] = v[2][j];
            }
            if (myrank == numProcs - 1)
            {
                for (j = 1; j <= space; j++)
                    v[mypoints + 1][j] = v[mypoints - 1][j];
            }


            if (myrank % 2)
            {

                MPI_Send(v[1], space + 2, MPI_DOUBLE, leftProc, 0, MPI_COMM_WORLD);
                MPI_Recv(v[0], space + 2, MPI_DOUBLE, leftProc, 0, MPI_COMM_WORLD, &status);
                MPI_Send(v[mypoints], space + 2, MPI_DOUBLE, rightProc, 0, MPI_COMM_WORLD);
                MPI_Recv(v[mypoints + 1], space + 2, MPI_DOUBLE, rightProc, 0, MPI_COMM_WORLD, &status);
            }
            else
            {
                MPI_Recv(v[mypoints + 1], space + 2, MPI_DOUBLE, rightProc, 0, MPI_COMM_WORLD, &status);
                MPI_Send(v[mypoints], space + 2, MPI_DOUBLE, rightProc, 0, MPI_COMM_WORLD);
                MPI_Recv(v[0], space + 2, MPI_DOUBLE, leftProc, 0, MPI_COMM_WORLD, &status);
                MPI_Send(v[1], space + 2, MPI_DOUBLE, leftProc, 0, MPI_COMM_WORLD);
            }

            for (i = 1; i <= mypoints; i++)
            {
                for (j = 1; j <= space; j++)
                {

                    ElecA1 = V1[1][(int)space / 2];


                    if (myrank == 0 && i == 2 && t <= stimtime && t>=10)
                        I_stim[i][j] = Istim;
                    else if (t >= secondstimstart && t <= secondstimstart + stimtime && j <= space / 2 && j >= 1)
                         // I_stim[i][j] = Istim;
                        v[i][j] = -53.0;
                    else
                        I_stim[i][j] = 0.0;


                 //   if (myrank == 5 && v[i][j] >= -50.0 && j<300 && j> 200 )
           // {
            //  v[i][j] == -54.0;   
           // }



                    mss = (1.0 / (1.0 + exp(-(v[i][j] + 35.9584) / 9.24013)));
                    hss = (1.0 / (1.0 + exp((v[i][j] + 57.0) / 8.0)));
                    mtc = (0.25 + 7.0 / (1.0 + exp((v[i][j] + 38.0) / 10.0)));
                    htc = (0.9 + 1002.85 / (1.0 + ((v[i][j] + 47.5) / 1.5) * ((v[i][j] + 47.5) / 1.5)));
                    ena = ((R * temp / frdy) * log(nao / nai));
                    ina[i][j] = (gna * (m[i][j] * m[i][j] * m[i][j]) * h[i][j] * (v[i][j] - ena));


                    fca = (1.0 / (1.0 + pow((cai[i][j] / kmca), 4.0)));
                    dss = (1.0 / (1.0 + exp(-(v[i][j] + 22.0) / 7.0)));
                    f1ss = (1.0 / (1.0 + exp((v[i][j] + 38.0) / 7.0)));
                    f2ss = f1ss;
                    dtc = (2.29 + 5.7 / (1.0 + ((v[i][j] + 29.97) / 9.0) * ((v[i][j] + 29.97) / 9.0)));
                    f1tc = (12.0);
                    f2tc = (90.9699 * (1.0 - (1.0 / (1.0 + exp((v[i][j] + 13.9629) / 45.3782))) * (1.0 / (1.0 + exp(-(v[i][j] + 9.49866) / 3.3945)))));
                    ical[i][j] = (gcal * fca * (d[i][j] * d[i][j]) * (0.8 * f1[i][j] + 0.2 * f2[i][j]) * (v[i][j] - ecal));


                    bss = (1.0 / (1.0 + exp(-(v[i][j] + 54.23) / 9.88)));
                    gss = (0.02 + (1.0 - 0.02) / (1.0 + exp((v[i][j] + 72.978) / 4.64)));
                    btc = (0.45 + 3.9 / (1.0 + ((v[i][j] + 66.0) / 26.0) * ((v[i][j] + 66.0) / 26.0)));
                    gtc = (150.0 * (1.0 - (1.0 / (1.0 + exp((v[i][j] - 417.43) / 203.18))) * (1.0 / (1.0 + exp(-(v[i][j] + 61.11) / 8.07)))));
                    icat[i][j] = (gcat * (b[i][j] * b[i][j]) * g[i][j] * (v[i][j] - ecat));


                    qss = (0.978613 / (1.0 + exp(-(v[i][j] + 18.6736) / 26.6606)));
                    r1ss = (1.0 / (1.0 + exp((v[i][j] + 63.0) / 6.3)));
                    r2ss = r1ss;
                    qtc = (500.0 / (1.0 + ((v[i][j] + 60.71) / 15.79) * ((v[i][j] + 60.71) / 15.79)));
                    r1tc = (5000.0 / (1.0 + ((v[i][j] + 62.7133) / 35.8611) * ((v[i][j] + 62.7133) / 35.8611)));
                    r2tc = (30000.0 + 220000.0 / (1.0 + exp((v[i][j] + 22.0) / 4.0)));
                    ek = ((R * temp / frdy) * log(ko / ki));
                    ik1[i][j] = (gk * gk1 * (q[i][j] * q[i][j]) * (0.38 * r1[i][j] + 0.63 * r2[i][j]) * (v[i][j] - ek));



                    pss = (0.948 / (1.0 + exp(-(v[i][j] + 17.91) / 18.4)));
                    k1ss = (1.0 / (1.0 + exp((v[i][j] + 21.2) / 5.7)));
                    k2ss = k1ss;
                    ptc = (100.0 / (1.0 + ((v[i][j] + 64.1) / 28.67) * ((v[i][j] + 64.1) / 28.67)));
                    k1tc = (1.0e6 * (1.0 - (1.0 / (1.0 + exp((v[i][j] - 315.0) / 50.0))) * (1.0 / (1.0 + exp(-(v[i][j] + 74.9) / 8.0)))));
                    k2tc = (1000.0 * 2500.0 * (1.0 - (1.0 / (1.0 + exp((v[i][j] - 132.868) / 25.3992))) * (1.0 / (1.0 + exp(-(v[i][j] + 24.9203) / 2.67915)))));
                    ik2[i][j] = (gk * gk2 * (p[i][j] * p[i][j]) * (0.75 * k1[i][j] + 0.25 * k2[i][j]) * (v[i][j] - ek));


                    xass_z = (-0.749234 / (1.0 + ((cai[i][j] * 1000.0 - 0.0630535) / 0.161942) * ((cai[i][j] * 1000.0 - 0.0630535) / 0.161942)) + 8.38384 / (1.0 + ((cai[i][j] * 1000.0 + 1538.29) / 739.057) * ((cai[i][j] * 1000.0 + 1538.29) / 739.057)));
                    xass_vh = (5011.47 / (1.0 + pow(((cai[i][j] * 1000.0 + 0.237503) / 0.000239278), 0.42291)) - 37.5137);
                    xass = (1.0 / (1.0 + exp(-xass_z * frdy * (v[i][j] - xass_vh) / (R * temp))));
                    xatc = (2.40914 / (1.0 + ((v[i][j] - 158.779) / (-52.1497)) * ((v[i][j] - 158.779) / (-52.1497))));
                    BKa[i][j] = (gkca * gbka * xa[i][j] * (v[i][j] - ek));


                    xabss_z = (-0.681249 / (1.0 + ((cai[i][j] * 1000.0 - 0.218988) / 0.428335) * ((cai[i][j] * 1000.0 - 0.218988) / 0.428335)) + 1.40001 / (1.0 + ((cai[i][j] * 1000.0 + 228.71) / 684.946) * ((cai[i][j] * 1000.0 + 228.71) / 684.946)));
                    xabss_vh = (8540.23 / (1.0 + pow(((cai[i][j] * 1000.0 + 0.401189) / 0.00399115), 0.668054)) - 109.275);
                    xabss = (1.0 / (1.0 + exp(-xabss_z * frdy * (v[i][j] - xabss_vh) / (R * temp))));
                    xabtc = (13.8049 / (1.0 + ((v[i][j] - 153.019) / 66.4952) * ((v[i][j] - 153.019) / 66.4952)));
                    BKab[i][j] = (gkca * gbkab * xab[i][j] * (v[i][j] - ek));


                    sss = (1.0 / (1.0 + exp(-(v[i][j] + 27.79) / 7.57)));
                    xss = (0.02 + 0.98 / (1.0 + exp((v[i][j] + 69.5) / 6.0)));
                    stc = (17.0 / (1.0 + ((v[i][j] + 20.5232) / 35.0) * ((v[i][j] + 20.5232) / 35.0)));
                    xtc = (7.5 + 10.0 / (1.0 + ((v[i][j] + 34.1765) / 120.0) * ((v[i][j] + 34.1765) / 120.0)));

                    ika[i][j] = (gk * gka * s[i][j] * x[i][j] * (v[i][j] - ek));


                    yss = (1.0 / (1.0 + exp((v[i][j] + 105.39) / 8.6553)));
                    ya = (3.5e-6 * exp(-0.0497 * v[i][j]));
                    yb = (0.04003 * exp(0.05211 * v[i][j]));
                    ytc = (1.0 / (ya + yb));
                    eh = ((R * temp / frdy) * log((ko + (PNa / PK) * nao) / (ki + (PNa / PK) * nai)));

                    ih[i][j] = (gh * y[i][j] * (v[i][j] - eh));


                    K1cl = (0.0006 * exp(2.53 * vFRT(v[i][j])));
                    K2cl = (0.1 * exp(-5.0 * vFRT(v[i][j])));
                    css = (1.0 / (1.0 + K2cl * ((K1cl / cai[i][j]) * (K1cl / cai[i][j]) + K1cl / cai[i][j] + 1.0)));
                    ctc = (-160.0 + 210.0 / (1.0 + exp((v[i][j] + 4.56) / 11.62)) + 170.0 / (1.0 + exp(-(v[i][j] + 25.5) / 11.62)));
                    ecl = (((R * temp) / frdy) * log(cli / clo));
                    icl[i][j] = (gcl * c[i][j] * (v[i][j] - ecl));



                    fmg = (0.108043 + 0.903902 / (1.0 + pow((mgo / 0.281007), 1.29834)));
                    enscc = ((R * temp / frdy) * log((PnsK * ko + PnsNa * nao + 4 * PnsCa * (1.0 / (1.0 + exp(vFRT(v[i][j])))) * cao) / (PnsK * ki + PnsNa * nai + 4 * PnsCa * (1.0 / (1.0 + exp(vFRT(v[i][j])))) * cai[i][j])));
                    insca = (fmg * (gs_ca(cao) * gnsCa) * gns * (v[i][j] - (enscc)));
                    insna = (fmg * (gs_x(nao) * gnsNa) * gns * (v[i][j] - (enscc)));
                    insk = (fmg * (gs_x(ko) * gnsK) * gns * (v[i][j] - (enscc)));
                    il = (fmg * (gl) * (v[i][j] - (enscc)));
                    inscc[i][j] = (insca + insna + insk + il);



                    f1naca = (exp((xgamma - 1.0) * vFRT(v[i][j])));
                    f2naca = (exp(xgamma * vFRT(v[i][j])));
                    fallo = (1.0 / (1.0 + pow((Kmallo / cai[i][j]), nallo)));
                    naca_Eup = (Jnaca * ((nai * nai * nai) * cao * f2naca - (nao * nao * nao) * cai[i][j] * f1naca));
                    naca_Ed1 = (1.0 + ksat * f1naca);
                    naca_Ed2 = (Kmcao * (nai * nai * nai) + (Kmnao * Kmnao * Kmnao) * cai[i][j] + (Kmnai * Kmnai * Kmnai) * cao * (1.0 + cai[i][j] / Kmcai));
                    naca_Ed3 = (cao * (nai * nai * nai) + (nao * nao * nao) * cai[i][j] + (nao * nao * nao) * Kmcai * (1.0 + (nai / Kmnai) * (nai / Kmnai) * (nai / Kmnai)));
                    jnaca = (fallo * naca_Eup / (naca_Ed1 * (naca_Ed2 + naca_Ed3)));

                    inaca[i][j] = (jnaca * ((zca * frdy) / (AV * Cm * buff)));


                    fnak = (1.0 / (1.0 + 0.1245 * exp(-0.1 * vFRT(v[i][j])) + 2.19e-3 * (exp(nao / 49.71)) * exp(-1.9 * vFRT(v[i][j]))));
                    knak = (1.0 / (1.0 + pow((nakKmko / ko), 1.5)));
                    nnak = (1.0 / (1.0 + pow((nakKmnai / nai), 2)));
                    inak[i][j] = (ginak * knak * nnak * fnak);



                    ib[i][j] = (gb * (v[i][j] - ek));


                    it[i][j] = ina[i][j] + ical[i][j] + icat[i][j] + ik1[i][j] + ik2[i][j] + BKa[i][j] + BKab[i][j] + ika[i][j] + ih[i][j] + icl[i][j] + inscc[i][j] + 0.5 * inaca[i][j] + inak[i][j] + ib[i][j];




                    wss = (1.0 / (1.0 + pow(((FKm * 1e-6) / cai[i][j]), Fn)));
                    wtc = (4000.0 * (0.234845 + ((1.0 - 0.234845) / (1.0 + pow((cai[i][j] / (FKm * 1e-6)), Fn)))));




                    jpmca = (Jpmca / (1.0 + pow((Kmpmca / cai[i][j]), npmca)));
                    jt[i][j] = (((AV * Cm * buff) / (zca * frdy)) * (ical[i][j] + icat[i][j] + insca) - jnaca + jpmca);

                    cai[i][j] += -dt * jt[i][j];





                    V1[i][j] = v[i][j] + dt * ((D[i][j] / (del_x * del_x)) * (v[i + 1][j] + v[i - 1][j] + v[i][j + 1] + v[i][j - 1] - 4 * v[i][j]) - (I_stim[i][j] + it[i][j] - n[i][j] * G_j[i][j] * (v_f[i][j] - v[i][j]) / C_m));
                    v_f[i][j] += (-dt / C_f) * (G_f * (v_f[i][j] - E_f) + G_j[i][j] * (v_f[i][j] - v[i][j]));




                    Ft[i][j] = Fmax * (w[i][j] - 0.2345);


                    ik[i][j] = ik1[i][j] + ik2[i][j] + BKa[i][j] + BKab[i][j] + ika[i][j] + ib[i][j];



                    m[i][j] += dt * ((mss - m[i][j]) / (mtc));
                    h[i][j] += dt * ((hss - h[i][j]) / (htc));
                    d[i][j] += dt * ((dss - d[i][j]) / (dtc));
                    f1[i][j] += dt * ((f1ss - f1[i][j]) / (f1tc));
                    f2[i][j] += dt * ((f2ss - f2[i][j]) / (f2tc));
                    b[i][j] += dt * ((bss - b[i][j]) / (btc));
                    g[i][j] += dt * ((gss - g[i][j]) / (gtc));
                    q[i][j] += dt * ((qss - q[i][j]) / (qtc));
                    r1[i][j] += dt * ((r1ss - r1[i][j]) / (r1tc));
                    r2[i][j] += dt * ((r2ss - r2[i][j]) / (r2tc));
                    p[i][j] += dt * ((pss - p[i][j]) / (ptc));
                    k1[i][j] += dt * ((k1ss - k1[i][j]) / (k1tc));
                    k2[i][j] += dt * ((k2ss - k2[i][j]) / (k2tc));
                    xa[i][j] += dt * ((xass - xa[i][j]) / (xatc));
                    xab[i][j] += dt * ((xabss - xab[i][j]) / (xabtc));
                    s[i][j] += dt * ((sss - s[i][j]) / (stc));
                    x[i][j] += dt * ((xss - x[i][j]) / (xtc));
                    y[i][j] += dt * ((yss - y[i][j]) / (ytc));
                    c[i][j] += dt * ((css - c[i][j]) / (ctc));
                    w[i][j] += dt * (wss - w[i][j]) / wtc;
                }
            }

            for (i = 1; i <= mypoints; i++)
            {
                for (j = 1; j <= space; j++)
                    v[i][j] = V1[i][j];
            }

            if (iter % interval == 0)
            {
                for (i = 1; i <= mypoints; i++)
                {
                    for (j = 1; j <= space; j++)
                        fwrite(&v[i][j], sizeof(double), 1, Vout[myrank]);
                }
            }


            if (iter % interval == 0)
            {
                for (i = 1; i <= mypoints; i++)
                {
                    for (j = 1; j <= space-1; j++)
                        fprintf(VoutM[myrank], "%f ", v[i][j]);


                    fprintf(VoutM[myrank], "%f\n" , v[i][j]);

                }
            }
        //     // if (myrank % 6 == 0)
            if (myrank % 1 == 0)
            {
                fprintf(Tser[myrank], "%f\n", ElecA1);
            }
        }

        // For making n distribution graph
        for (i = 1; i <= mypoints; i++)
        {

            for (j = 1; j < space - 1; j++)
            {
                fprintf(Nout[myrank], "%f ", n[i][j]);
            }

            fprintf(Nout[myrank], "%f\n", n[i][space]);
        }

        fclose(Vout[myrank]);
        fclose(VoutM[myrank]);
        // fclose(F_n);
        fclose(Tser[myrank]);
        fclose(Nout[myrank]);
    }
    endtime = MPI_Wtime();
    if (myrank == 0)
    {
        MPI_Get_processor_name(procname, &namelen);
        printf("---------------------------------------------\n");
        printf("CLUSTER NAME: %s\n", procname);
        printf("---------------------------------------------\n");
    }
    printf("time in %02d th processor is %f seconds\n", myrank, endtime - starttime);

    int Proc = numProcs;



    FILE  *F2;
    double vv[mypoints * space];
    int nn[mypoints * space];
    for (run = run_min; run <= run_max; run++)
    {
        strcpy(name, datdir);
        sprintf(RUN, "run%d/", run);
        strcat(name, RUN);
        sprintf(filename, "VmyoData.dat");
        strcat(name, filename);
        printf("%s\n", name);
        F2 = fopen(name, "w");
        for (i = 0; i < numProcs; i++)
        {
            strcpy(name, datdir);
            strcat(name, RUN);
            sprintf(filename, "myo1p%02d.dat", i);
            strcat(name, filename);

            Vout[i] = fopen(name, "r");
        }

        for (iter = 1; iter < (maxtime / interval) + 0.5; iter++)
        {
            for (i = 0; i < numProcs; i++)
            {
                fread(vv, sizeof(double), mypoints * space, Vout[i]);
                fwrite(vv, sizeof(double), mypoints * space, F2);
            }
        }
        for (i = 0; i < numProcs; i++)
            fclose(Vout[i]);
        fclose(F2);
        strcpy(name, datdir);
        strcat(name, RUN);
        sprintf(filename, "random.dbl");
        strcat(name, filename);

        F2 = fopen(name, "w");
        for (i = 0; i < numProcs; i++)
        {
            strcpy(name, datdir);
            strcat(name, RUN);
            sprintf(filename, "random%04d.dbl", i);
            strcat(name, filename);

            Vout[i] = fopen(name, "r");
        }

        for (i = 0; i < numProcs; i++)
        {
            fread(nn, sizeof(int), mypoints * space, Vout[i]);
            fwrite(nn, sizeof(int), mypoints * space, F2);
        }


        sprintf(filename, "rm -f /localscratch/ughima/data/run%d/myo1p*", run);
        system(filename);
        sprintf(filename, "rm -f /localscratch/ughima/data/run%d/random0*", run);
        system(filename);

        printf("%s\n", "accumulate functioned properly.");
    }





    MPI_Finalize();

    return 0;
}

