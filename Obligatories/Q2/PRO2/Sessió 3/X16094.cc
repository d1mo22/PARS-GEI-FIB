#include "Estudiant.hh"

/* Constants */

const char *ER1 = "No te nota";
const char *ER2 = "Valor de la nota entre 0 a 10";
const char *ER3 = "Ja te nota";
const char *ER4 = "El DNI es incorrecte";

Estudiant::Estudiant(){
  dni=0;
  nota = -1;
}

Estudiant::Estudiant(int dni)
{
  if (dni<0) throw PRO2Excepcio(ER4);
  this->dni = dni;
  nota = -1;
}
/*
Estudiant::Estudiant(const Estudiant& est) {
    
    dni = est.dni;
    nota = est.nota;
    
}
*/

void Estudiant::afegir_nota(double nota)
{
  if (this->nota != -1) 
    throw PRO2Excepcio(ER3);
  if (nota<0 or nota>MAX_NOTA)
    throw PRO2Excepcio(ER2); 
  
  this->nota = nota; 
  //amb_nota = true;
}

void Estudiant::modificar_nota(double nota)
{ 				
  if (this->nota == -1) 
    throw PRO2Excepcio(ER1);
  if (nota<0 or nota>MAX_NOTA)
    throw PRO2Excepcio(ER2);
  this->nota = nota;
}

bool Estudiant::te_nota() const 
{
  return nota != -1;
}

double Estudiant::consultar_nota() const
{
  if (nota == -1) throw PRO2Excepcio(ER1);
  return nota;
}

int Estudiant::consultar_DNI() const
{
  return dni;
}

double Estudiant::nota_maxima()
{
  return MAX_NOTA;
}

bool Estudiant::comp(const Estudiant& e1, const Estudiant& e2){
  /* Pre: cert  */
  /* Post: el resultat indica si e1 te dni mes petit que e2 */
  
  return e1.consultar_DNI() < e2.consultar_DNI();
  
}
void Estudiant::llegir()
{
  cin >> dni;
  if (dni<0) throw PRO2Excepcio(ER4);
  double x;
  cin >> x;
  if (x >= 0 and x <= MAX_NOTA) {
    nota = x; 
    //amb_nota = true;
  }
  else /*amb_nota = false*/ nota = -1;
}

void Estudiant::escriure() const
{
  if (nota != -1)
    cout << dni << " " << nota << endl;
  else
    cout << dni <<" NP" << endl;
}

bool Estudiant::operator==(const Estudiant& est) const 
{
  return dni == est.dni;
}

bool Estudiant::operator!=(const Estudiant& est) const 
{
  return dni != est.dni;
}