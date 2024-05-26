#version 330 core

in vec3  fmatamb;
in vec3  fmatdiff;
in vec3  fmatspec;
in float fmatshin;

in vec3  fvertex;
in vec3  fnormal;
in vec3 fCar1;
in vec3 fCar2;

const vec3 llumAmbient = vec3(0.1, 0.1, 0.1);
uniform vec3 colCam;
const vec3 colLightCar = vec3(0.6, 0.6, 0.0);

out vec4 FragColor;

uniform vec3 posFocusCam;
uniform int camara;

vec3 Ambient() {
  return llumAmbient*fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) {
  // Fixeu-vos que SOLS es retorna el terme de Lambert!
  // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
  vec3 colRes = vec3(0);
  if (dot (L, NormSCO) > 0)
    colRes = colFocus * fmatdiff * dot (L, NormSCO);
  return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec3 vertSCO, vec3 colFocus) {
  // Fixeu-vos que SOLS es retorna el terme especular!
  // Assumim que els vectors estan normalitzats
  vec3 colRes = vec3 (0);
  // Si la llum ve de darrera o el material és mate no fem res
  if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
    return colRes;  // no hi ha component especular

  vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
  vec3 V = normalize(-vertSCO); // perquè la càmera està a (0,0,0) en SCO

  if (dot(R, V) < 0)
    return colRes;  // no hi ha component especular

  float shine = pow(max(0.0, dot(R, V)), fmatshin);
  return (colRes + fmatspec * colFocus * shine);
}

void main() {
  vec3 LCam = normalize(posFocusCam - fvertex);
  vec3 LCar1 = normalize(fCar1 - fvertex);
  vec3 LCar2 = normalize(fCar2 - fvertex);

  vec3 normal = normalize(fnormal);
  
  vec3 ambient = Ambient();

  vec3 difus = vec3(0);
  difus += Difus(normal, LCam, colCam);
  difus += Difus(normal, LCar1, colLightCar);
  difus += Difus(normal, LCar2, colLightCar);

  vec3 especular = vec3(0);
  especular += Especular(normal, LCam, fvertex, colCam);
  especular += Especular(normal, LCar1, fvertex, colLightCar);
  especular += Especular(normal, LCar2, fvertex, colLightCar);

  //vec3 fcolor = ambient + difusCam + especularCam + difusCar1 + especularCar1 + difusCar2 + especularCar2;
  FragColor = vec4(ambient+difus+especular, 1);
}
