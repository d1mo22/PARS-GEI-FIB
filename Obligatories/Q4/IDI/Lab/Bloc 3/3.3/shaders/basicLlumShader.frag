#version 330 core

in vec3 fcolor;
out vec4 FragColor;

in vec3 fmatamb;
in vec3 fmatdiff;
in vec3 fmatspec;
in float fmatshin;

in vec3 fVertexSCO;
in vec3 fNormalSCO;
in vec3 fposFSCO;

uniform vec3 colorFocusA; //vec3(0.8,0.8,0.8);
uniform vec3 colorFocusC;
vec3 llumAmbient = vec3(0.2, 0.2, 0.2);
uniform vec3 posFocusC;  // en SCA / SCO si es luz de camara
uniform int focusCamara;
uniform int llum_ambient;
uniform int llum_camara;

//Normalizar 

vec3 Ambient() {
    return llumAmbient * fmatamb;
}

vec3 Difus (vec3 NormSCO, vec3 L, vec3 colFocus) 
{
    // Tant sols retorna el terme difús
    // S'assumeix que els vectors que es reben com a paràmetres estan normalitzats
    vec3 colRes = vec3(0);
    // Càlcul component difusa, si n'hi ha
    if (dot (L, NormSCO) > 0)
      colRes = colFocus * fmatdiff * dot (L, NormSCO);
    return (colRes);
}

vec3 Especular (vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) 
{
    // Tant sols retorna el terme especular!
    // Els vectors rebuts com a paràmetres (NormSCO i L) estan normalitzats
    vec3 colRes = vec3 (0);
    // Si la llum ve de darrera o el material és mate no fem res
    if ((dot(NormSCO,L) < 0) || (fmatshin == 0))
      return colRes;  // no hi ha component especular

    // Calculem R i V
    vec3 R = reflect(-L, NormSCO); // equival a: 2.0*dot(NormSCO,L)*NormSCO - L;
    vec3 V = normalize(-vertSCO.xyz); // perquè la càmera està a (0,0,0) en SCO

    if (dot(R, V) < 0)
      return colRes;  // no hi ha component especular
    
    // Calculem i retornem la component especular
    float shine = pow(max(0.0, dot(R, V)), fmatshin);
    return (fmatspec * colFocus * shine); 
}

void main()
{	
	//Calcular la L aqui
	vec3 NormalSCO = normalize(fNormalSCO);
	vec3 LA, LC;
	
	LC = normalize(posFocusC - fVertexSCO);
	LA = normalize(fposFSCO - fVertexSCO);
	

	vec3 ambient = Ambient();

  vec3 difusC = Difus(NormalSCO, LC, colorFocusA);
  vec3 difusA = Difus(NormalSCO, LA, colorFocusC);
  vec3 difus;

  if (llum_camara == 1) difus += difusC;
  
  if (llum_ambient == 1) difus += difusA;
  
  vec3 especularC = Especular(NormalSCO, LC, vec4(fVertexSCO,1.0), colorFocusA);
  vec3 especularA = Especular(NormalSCO, LA, vec4(fVertexSCO,1.0), colorFocusC);
  vec3 especular;

  if (llum_camara == 1) especular += especularC;

  if (llum_ambient == 1) especular += especularA;
   

	FragColor = vec4(ambient+difus+especular,1);	
}
