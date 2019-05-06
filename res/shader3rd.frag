#version 400

layout( location = 0 ) out vec4 fragcolor;

 in  vec3 FragPos;
 in  vec3 normal;
 in  vec2 texCoords;


uniform sampler2D appliedTexture;
uniform vec3 lightPos;
uniform vec3 cameraPos;
uniform int switch1;
uniform float counterR;
uniform float counterG;
uniform float counterB;


float tr;
float tg;
float tb;



void main()
{           


fragcolor = vec4(texture(appliedTexture, texCoords));

if (switch1 < 1){

}

if (switch1 == 1){
 //Color inverting
fragcolor.r = 1.0 - fragcolor.r;
fragcolor.g = 1.0 - fragcolor.g;
fragcolor.b = 1.0 - fragcolor.b;
}

if (switch1 == 2){

//Sepia toning

tr = (fragcolor.r * 0.393) + (fragcolor.g * 0.769) + (fragcolor.b * 0.189);
tg = (fragcolor.r * 0.349) + (fragcolor.g * 0.686) + (fragcolor.b * 0.168);
tb = (fragcolor.r * 0.272) + (fragcolor.g * 0.534) + (fragcolor.b * 0.131);

fragcolor.r = tr;
fragcolor.g = tg;
fragcolor.b = tb;


}
 
 if (switch1 == 3){
 //greyscale
 

fragcolor.r *= 0.2126;
fragcolor.g *= 0.7152;
fragcolor.b *= 0.0722;

float yLinear = fragcolor.r + fragcolor.g + fragcolor.b;

fragcolor.r = yLinear;
fragcolor.g = yLinear;
fragcolor.b = yLinear;

 }

 if (switch1 == 4) {
 //Red Monochrome
 fragcolor.g = 0;
 fragcolor.b = 0;
 }

 if (switch1 == 5) {
 //Green Monochrome
 fragcolor.r = 0;
 fragcolor.b = 0;
 }

 if (switch1 == 6) {
 //Blue Monochrome
 fragcolor.g = 0;
 fragcolor.r = 0;
 }

 if (switch1 > 6){
 //Ping-pong between values
 fragcolor.r -= counterR;
 fragcolor.g -= counterG,
 fragcolor.b -= counterB;
 }

    //Phong lighting
    // ambient
    vec3 ambient = 0.05 * fragcolor.rgb;
    // diffuse
    vec3 lightDirection = normalize(lightPos - FragPos);
    vec3 normal = normalize(normal);
    float diff = max(dot(lightDirection, normal), 0.0);
    vec3 diffuse = diff * fragcolor.rgb;
    // specular
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDirection = reflect(-lightDirection, normal);
   
   float spec = pow(max(dot(viewDir, reflectDirection), 0.0), 8);
   
    vec3 specular = vec3(0.5) * spec; //The vector represents light colour
    vec4 color1 = vec4(ambient + diffuse + specular, 1.0);
	fragcolor += color1;

	
	//Apply gamma correction
	 float gamma = 2.2;
     fragcolor.rgb = pow(fragcolor.rgb, vec3(1.0/gamma));
	 
	
	//clamp the rbg color values
	clamp(fragcolor.r, 0.0, 1.0);
    clamp(fragcolor.g, 0.0, 1.0);
    clamp(fragcolor.b, 0.0, 1.0);
}