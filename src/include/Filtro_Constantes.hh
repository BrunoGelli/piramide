#ifndef Filtro_Constantes_h
#define Filtro_Constantes_h 1

// FILTRO_LARGURA_CM - Largura do filtro em cm
//# define FILTRO_LARGURA_CM 0.2 * cm

// RAIO_CM - Distancia em cm da posicao inicial ate a origem
# define RAIO_CM 1.0 * cm

// PRINT_FILE - 1 = imprime informacoes no arquivo TXT_FILE; 0 = nao faz nada
#define PRINT_FILE 0

// TXT_FILE - nome do arquivo no qual sera impresso dimensoes e eficiencia
#define TXT_FILE "FiltroOutPut.txt"

// BARRA_NOME - barra centralizada no sipm a qual guiara os fotons
#define BARRA_NOME "Barra_central"

// SIPM_NOME - Detector de SiliconM dos fotons
#define SIPM_NOME "SiPM_1"

// FILTRO_NOME - regiao onde tera argonio
#define FILTRO_NOME "Filtro"

// MUNDO_NOME - regiao de teflom
#define MUNDO_NOME "World"

// IMPRIMIR_EVENTOS - imprime ou nao informacoes do evento atual
#define IMPRIMIR_EVENTOS false

const double AngleProb[9] = 
{
	  0.00,
	  5.30,
	 20.50,
	 45.42,
	 65.91,
	 81.62,
	 90.65,
	 97.09,
	100.00
};

const double Angle[9] = 
{
	 0,
	 5,
	15,
	25,
	35,
	45,
	55,
	65,
	75
};


const double MuonMomentum[15] = 
{
	1.31E-01,
	2.13E-01,
	3.42E-01,
	5.53E-01,
	8.81E-01,
	1.43E+00,
	2.30E+00,
	3.69E+00,
	5.96E+00,
	9.59E+00,
	1.55E+01,
	2.49E+01,
	4.02E+01,
	6.47E+01,
	1.05E+02
};

const double MuonMomentumPDF[15][8] =
{
	{3.48E+01, 4.59E+02, 4.27E+02, 2.30E+02, 1.24E+02, 8.78E+01, 4.91E+01, 2.44E+01},
	{3.28E+01, 3.48E+02, 3.76E+02, 2.14E+02, 1.35E+02, 4.33E+01, 4.74E+01, 2.26E+01},
	{3.51E+01, 3.23E+02, 2.84E+02, 1.76E+02, 1.20E+02, 5.30E+01, 3.90E+01, 1.72E+01},
	{3.73E+01, 3.03E+02, 3.27E+02, 1.99E+02, 1.03E+02, 5.11E+01, 2.35E+01, 1.08E+01},
	{2.86E+01, 2.49E+02, 2.36E+02, 1.52E+02, 9.93E+01, 4.38E+01, 2.55E+01, 6.22E+00},
	{2.11E+01, 1.71E+02, 1.93E+02, 1.20E+02, 7.87E+01, 4.23E+01, 2.37E+01, 6.49E+00},
	{1.26E+01, 1.10E+02, 1.17E+02, 7.81E+01, 5.76E+01, 2.75E+01, 1.60E+01, 6.27E+00},
	{6.82E+00, 5.95E+01, 6.43E+01, 4.69E+01, 3.46E+01, 2.09E+01, 1.17E+01, 4.24E+00},
	{3.16E+00, 2.57E+01, 3.24E+01, 2.41E+01, 1.78E+01, 1.03E+01, 7.03E+00, 3.64E+00},
	{1.21E+00, 1.14E+01, 1.10E+01, 1.14E+01, 7.47E+00, 4.89E+00, 3.91E+00, 2.02E+00},
	{4.30E-01, 3.99E+00, 5.05E+00, 3.64E+00, 3.03E+00, 2.06E+00, 2.00E+00, 1.31E+00},
	{1.25E-01, 1.16E+00, 1.27E+00, 8.48E-01, 9.66E-01, 8.34E-01, 5.91E-01, 6.22E-01},
	{3.29E-02, 3.55E-01, 4.86E-01, 4.02E-01, 3.21E-01, 2.56E-01, 2.39E-01, 1.99E-01},
	{7.68E-03, 9.09E-02, 1.31E-01, 7.99E-02, 1.30E-01, 6.45E-02, 1.01E-01, 8.70E-02},
	{2.32E-03, 5.70E-02, 7.96E-02, 1.16E-02, 3.14E-02, 1.83E-02, 6.05E-02, 2.47E-02}
};

#endif
