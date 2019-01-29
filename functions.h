/*Some functions an constants required for computation*/
double gs_x(double conc)
{
    return ((0.03 / (1 + (150.0 / (conc + 1e-8)) * (150.0 / (conc + 1e-8)))) / 0.0123); // Extracellular ionic concentrations dependency on INSCC conductance
}

double gs_ca(double conc)
{
    return ((0.03 / (1 + (150.0 / (conc + 1e-8)) * (150.0 / (conc + 1e-8)))) / 0.000525); // Extracellular calcium concentrations
}

double R = 8314.472;      // Universal Gas Constant (J/kmol*K)
double frdy = 96485.3415; // Faraday's Constant (C/mol)
double temp = 308.0;      // Temperature (K)
double Cm = 1.0;          // Specific membrane capacitance (uF/cm2)

double vFRT(double potential)
{
    return ((potential * frdy) / (R * temp)); // common function for ICl, INSCC INaK, INaCa
}
/* Constants */
double zca = 2.0; // Valency for Ca2+
double zna = 1.0; // Valency for Na+
double zk = 1.0;  // Valency for K+
