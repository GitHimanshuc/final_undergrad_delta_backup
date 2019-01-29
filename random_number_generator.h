//==================================================== file = genpois.c =====
//=  Program to generate Poisson distributed random variables               =
//===========================================================================
//=  Notes: 1) Writes to a user specified output file                       =
//=         2) Generates user specified number of values                    =
//=-------------------------------------------------------------------------=
//= Example user input:                                                     =
//=                                                                         =
//=   ---------------------------------------- genpois.c -----              =
//=   -  Program to generate Poisson random variables        -              =
//=   --------------------------------------------------------              =
//=   Output file name ===================================> output.dat      =
//=   Random number seed =================================> 1               =
//=   Rate in customers per second =======================> 10.0            =
//=   Number of values to generate =======================> 5               =
//=   --------------------------------------------------------              =
//=   -  Generating samples to file                          -              =
//=   --------------------------------------------------------              =
//=   --------------------------------------------------------              =
//=   -  Done!                                                              =
//=   --------------------------------------------------------              =
//=-------------------------------------------------------------------------=
//= Example output file ("output.dat" for above):                           =
//=                                                                         =
//=   0                                                                     =
//=   9                                                                     =
//=   6                                                                     =
//=   10                                                                    =
//=   13                                                                    =
//=-------------------------------------------------------------------------=
//=  Build: bcc32 genpois.c                                                 =
//=-------------------------------------------------------------------------=
//=  Execute: genpois                                                       =
//=-------------------------------------------------------------------------=
//=  Author: Ken Christensen                                                =
//=          University of South Florida                                    =
//=          WWW: http://www.csee.usf.edu/~christen                         =
//=          Email: christen@csee.usf.edu                                   =
//=-------------------------------------------------------------------------=
//=  History: KJC (05/25/06) - Genesis (from genexp.c)                      =
//===========================================================================

//----- Function prototypes -------------------------------------------------
int    poisson(double x);       // Returns a Poisson random variable
double expon(double x);         // Returns an exponential random variable
double rand_val(int seed);      // Jain's RNG

//===== Main program ========================================================
void generate_poisson(double lambda, int num_values, int filenumber, int seed, int run)
{
  FILE     *fp;                 // File pointer to output file
  char     file_name[256];      // Output file name string
  char     filenumb[5];         // Output file number
  int      pois_rv;             // Poisson random variable
  int      i;                   // Loop counter




  sprintf(filenumb,"%04d",filenumber);
  strcpy(file_name,datdir);
  sprintf(RUN,"run%d/",run);
  strcat(file_name,RUN);

  strcat(file_name,"random");
  strcat(file_name,filenumb);
  strcat(file_name,".dbl");
  fp = fopen(file_name, "wb");
  if (fp == NULL)
  {
    printf("ERROR in creating output file (%s) \n", file_name);
    exit(1);
  }
  rand_val(seed+run*1000);

  // Generate and output exponential random variables
  for (i=0; i<num_values; i++)
  {
    pois_rv = poisson(1.0 / lambda);
    fwrite(&pois_rv,sizeof(int),1,fp);
  }
  fclose(fp);
}

//===========================================================================
//=  Function to generate Poisson distributed random variables              =
//=    - Input:  Mean value of distribution                                 =
//=    - Output: Returns with Poisson distributed random variable           =
//===========================================================================
int poisson(double x)
{
  int    poi_value;             // Computed Poisson value to be returned
  double t_sum;                 // Time sum value

  // Loop to generate Poisson values using exponential distribution
  poi_value = 0;
  t_sum = 0.0;
  while(1)
  {
    t_sum = t_sum + expon(x);
    if (t_sum >= 1.0) break;
    poi_value++;
  }
  return(poi_value);
}

//===========================================================================
//=  Function to generate exponentially distributed random variables        =
//=    - Input:  Mean value of distribution                                 =
//=    - Output: Returns with exponentially distributed random variable     =
//===========================================================================
double expon(double x)
{
  double z;                     // Uniform random number (0 < z < 1)
  double exp_value;             // Computed exponential value to be returned

  // Pull a uniform random number (0 < z < 1)
  do
  {
    z = rand_val(0);
  }
  while ((z == 0) || (z == 1));

  // Compute exponential random variable using inversion method
  exp_value = -x * log(z);

  return(exp_value);
}

//=========================================================================
//= Multiplicative LCG for generating uniform(0.0, 1.0) random numbers    =
//=   - x_n = 7^5*x_(n-1)mod(2^31 - 1)                                    =
//=   - With x seeded to 1 the 10000th x value should be 1043618065       =
//=   - From R. Jain, "The Art of Computer Systems Performance Analysis," =
//=     John Wiley & Sons, 1991. (Page 443, Figure 26.2)                  =
//=========================================================================
double rand_val(int seed)
{
  const long  a =      16807;  // Multiplier
  const long  m = 2147483647;  // Modulus
  const long  q =     127773;  // m div a
  const long  r =       2836;  // m mod a
  static long x;               // Random int value
  long        x_div_q;         // x divided by q
  long        x_mod_q;         // x modulo q
  long        x_new;           // New x value

  // Set the seed if argument is non-zero and then return zero
  if (seed > 0)
  {
    x = seed;
    return(0.0);
  }

  // RNG using integer arithmetic
  x_div_q = x / q;
  x_mod_q = x % q;
  x_new = (a * x_mod_q) - (r * x_div_q);
  if (x_new > 0)
    x = x_new;
  else
    x = x_new + m;

  // Return a random value between 0.0 and 1.0
  return((double) x / m);
}
