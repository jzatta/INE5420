#include "colors.inc"
#include "stones.inc"
#include "textures.inc"
#include "shapes.inc"
#include "glass.inc" 
#include "metals.inc" 
#include "woods.inc"
  
background{ color Cyan}                        
                    
camera {   
    fisheye
    right x*1280/1024      
    angle 90  
    location <-1, 1, -1> 
    look_at  <-0.08, 1, 0>    
}                      
#declare T_Cushion= texture{
    pigment {color Yellow} 
    finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}
}
 
#declare T_Cushion_Blue= texture{
    pigment {color Blue} 
    finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}
} 
  
/*     
camera {   
    //fisheye
    right x*1280/1024      
    angle 90  
    location <-1, 2, 20> 
    look_at  <10, 1,  30>       
     
} */   

/*camera {   
    //fisheye
    right x*1280/1024      
    angle 90  
    location <30, 2, -4> 
    look_at  <30,5.9,  40>       
      
} */  
      
light_source { <2, 4, -3> color White}
light_source { <20, 9.99, 20> color White shadowless}

union{
difference { 
 box {
    <-5, -2, -5>,  
    < 401, 11,  70.5>   
    pigment {
      checker color LightWood, Flesh      
                    
    }
   // rotate y*-15     
  }
  
  box {
    < -1.5, -1, -4>,  
    < 400, 10,  70>   
    pigment {
     checker color LightWood, Flesh    
                    
    }
    finish {
    diffuse 0.6
    specular 1
    ambient 0.3
    }
   // rotate y*-15     
  }

//janelas  
#declare i=-0.5;
#declare j = 4;
    #while (i < 85)           
      box { <i, -0.5, 72>, <j, 2.5, 70> }
      box { <i, 3, 72>, <j, 7.5, 70> }
      box { <i, 8, 72>, <j, 9.5, 70> }
      #declare i = i+6;
      #declare j = j+6;
    #end
#declare i= 100;
#declare j = 104.5;
    #while (i < 400)           
      box { <i, -0.5, 72>, <j, 2.5, 70> }
      box { <i, 3, 72>, <j, 7.5, 70> }
      box { <i, 8, 72>, <j, 9.5, 70> }
      #declare i = i+6;
      #declare j = j+6;
    #end

}

//luzes 
#declare i=10;
#while (i<70)
    box { <i, 9.99, 4>, <i+3, 10.5, 7> pigment{color White} finish {specular 1 diffuse 1 ambient 1} }
    #declare i = i+9;
#end

#declare i=15;
#while (i<65)
    #declare j = 0; 
    #while (j<200)
        box { <j, 9.8, i>, <j + 0.5, 10.5, i+3> pigment{color White} finish {specular 1 diffuse 1 ambient 1} }
        #declare j = j + 10;
    #end
    #declare i = i+10;
#end

//espelho do lado
box {<-1.5, -1,-1.5>, <-1.49, 8, 20> texture {Chrome_Metal}}

//teto
box {<-1.5, 9.999, -4>, <400, 11, 70> texture {Cork}}
    
//parede no meio das janelas
box {<88.5, -1, 69.8>, <100, 10, 70.8> texture {White_Wood scale 0.01}} 

}



//pilar
union {
    box {
        < 70, -1, 20>,  
        < 80, 10,  27>
       // translate <-40, 1, -15>
       // rotate -2*y
       // translate <40, -1, 15>   
        /*pigment {
         color Goldenrod    
        }
        finish {
        //ambient .5
        diffuse .7
        reflection 0.1
        specular 1
        }*/
        texture {White_Wood scale 0.01}
    }
    box{<69, 0.9, 19>,<70, 1, 28> pigment {color Goldenrod}} 
    box{<69, 0.9, 19>, <81, 1, 20> pigment {color Goldenrod}} 
    
    box {
        <70.1, 3, 22>, <69.99, 7, 25>
        pigment {
         color CadetBlue
        }
    }     
}         

//parede com quadro vermelho
union {
    box {
        < 75, -1, 11>,  
        < 120, 10,  -5>   
        texture {White_Wood scale 0.01}
    }
    box {
        <75.1, 0.5, 5>, <74.9, 9, -4>
        pigment {
         color Red
        }
    }
}

//puff amarelo 1
box {
 <0,0,0>, <1.7,1.9,1.7>
 rotate y*45
 scale 0.8
 translate <43,-1, 4.5>
    texture {
         T_Cushion
    }
}

//puff amarelo 2      
box {
 <0,0,0>, <1.7,1.9,1.7>
 rotate y*55
 scale 0.6
 translate <25,-1, 4.5>
    texture {
        T_Cushion
    }
        
}

//puff amarelo 3
box {
 <0,0,0>, <1.7,1.9,1.7>
 rotate y*35
 scale 0.5
 translate <15,-1, 4>
    texture {
        T_Cushion
    }
}

//puff atras do 3
box {
 <0,0,0>, <1.7,1.9,1.7>
 //rotate y*35
 scale 0.5
 translate <17.5,-1, 4>
    texture {
        T_Cushion
    }
}


//puff redondo amarelo 1
difference {
    sphere{ 
        <0,-0.5,0>, 1
        texture {
            T_Cushion
        }
    }
    
    sphere {
        <0, 0.8, -0.35>, 1.4
        texture {
            T_Cushion
        }
    }
    
    translate <14,0.1,5.5>
    scale 1.2
}

//puff redondo amarelo 2
difference {
    sphere{ 
        <0,-0.5,0>, 1
        texture {
            T_Cushion
        }
    }
    
    sphere {
        <0, 0.8, -0.35>, 1.4
        texture {
            T_Cushion
        }
    }
    rotate y*30
    translate <17,0.1,5.5>
    scale 1.2
}

//puff redondo azul 1
difference {
    sphere{ 
        <0,-0.5,0>, 1
        texture {
            T_Cushion_Blue
        }
    }
    
    sphere {
        <0, 0.8, -0.35>, 1.4
        texture {
            T_Cushion_Blue
        }
    }
    rotate y*10
    translate <23,0.1,5.7>
    scale 1.2
}

//puff redondo azul 2
difference {
    sphere{ 
        <0,-0.5,0>, 1
        texture {
            T_Cushion_Blue
        }
    }
    
    sphere {
        <0, 0.8, -0.35>, 1.4
        texture {
            T_Cushion_Blue
        }
    }
    rotate y*10
    translate <32,0.21,4.5>
    scale 1.6
}

//estantes

#declare i=50;
#while (i < 150)
    union {
        box {
             <i, -1, 50>, <i+4, 3, 69>
             pigment {
                Candy_Cane
                scale 0.5
                rotate x*90
             }
             
        }
        
        box {
             <i, -1, 49.99>, <i+4, 3, 50.1>
             pigment { Gray}
        }
        box {
             <i-0.01, -1, 50>, <i, -0.2, 69>
             pigment { Gray}
        }
        box {
             <i-0.01, 1, 50>, <i, 1.8, 69>
             pigment { Gray}
        }
        box {
            <i, 2.3, 49.95>, <i+4, 3.8, 50>
            pigment{
                color OldGold
            }
           
        }
    }
#declare i = i+10; 
#end
            
//mesa de madeira do canto esquerdo
union {
    box {<-8, 0.5, -3>, <-5, 1, -0.5> texture {DMFWood3}}
    box {<-8, -1, -3>, <-7.8, 0.5, -2.8> texture {DMFWood3}}
    box {<-8, -1, -0.5>, <-7.8, 0.5, -0.7> texture {DMFWood3}}
    box {<-5, -1, -3>, <-5.2, 0.5, -2.8> texture {DMFWood3}}
    box {<-5, -1, -0.5>, <-5.2, 0.5, -0.7> texture {DMFWood3}}
    rotate -18*y
    translate <6.2, 0, 20>
} 

//mesa estudo 1 (perto do pilar)
union {
    //topo
    box {<-8, 0.6, -3>, <-6, 0.75, -0.5> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.1>, <-7.1, 0.75, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, -0.4>, <-7.1, 0.75, -0.5> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.1>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -3.1>, <-6, 0.6, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, -0.6>, <-6, -0.85, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -0.6>, <-6, 0.6, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, 0.15, -0.4>, <-7.1, 0.6, -3> pigment {color Goldenrod}} 
    translate <55, 0, 24>
    //scale 0.8
}

//mesa estudo 2
union {
    //topo
    box {<-8, 0.6, -3>, <-6, 0.75, -0.5> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.1>, <-7.1, 0.75, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, -0.4>, <-7.1, 0.75, -0.5> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.1>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -3.1>, <-6, 0.6, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, -0.6>, <-6, -0.85, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -0.6>, <-6, 0.6, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, 0.15, -0.4>, <-7.1, 0.6, -3> pigment {color Goldenrod}} 
    translate <45, 0, 24>
    //scale 0.8
}

//mesa estudo 3
union {
    //topo
    box {<-8, 0.6, -3>, <-6, 0.75, -0.5> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.1>, <-7.1, 0.75, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, -0.4>, <-7.1, 0.75, -0.5> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.1>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -3.1>, <-6, 0.6, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, -0.6>, <-6, -0.85, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -0.6>, <-6, 0.6, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, 0.15, -0.4>, <-7.1, 0.6, -3> pigment {color Goldenrod}} 
    translate <35, 0, 24>
    //scale 0.8
}

//mesa estudo 4
union {
    //topo
    box {<-8, 0.6, -3>, <-6, 0.75, -0.5> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.1>, <-7.1, 0.75, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, -0.4>, <-7.1, 0.75, -0.5> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.1>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -3.1>, <-6, 0.6, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, -0.6>, <-6, -0.85, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -0.6>, <-6, 0.6, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, 0.15, -0.4>, <-7.1, 0.6, -3> pigment {color Goldenrod}} 
    translate <35, 0, 30>
    //scale 0.8
}

//mesa estudo 5
union {
    //topo
    box {<-8, 0.6, -3>, <-6, 0.75, -0.5> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.1>, <-7.1, 0.75, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, -0.4>, <-7.1, 0.75, -0.5> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.1>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -3.1>, <-6, 0.6, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, -0.6>, <-6, -0.85, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -0.6>, <-6, 0.6, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, 0.15, -0.4>, <-7.1, 0.6, -3> pigment {color Goldenrod}} 
    translate <45, 0, 30>
    //scale 0.8
}

//mesa estudo 5
union {
    //topo
    box {<-8, 0.6, -3>, <-6, 0.75, -0.5> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.1>, <-7.1, 0.75, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, -0.4>, <-7.1, 0.75, -0.5> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.1>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -3.1>, <-6, 0.6, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, -0.6>, <-6, -0.85, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 0.75, -0.6>, <-6, 0.6, -0.5> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, 0.15, -0.4>, <-7.1, 0.6, -3> pigment {color Goldenrod}} 
    translate <55, 0, 30>
    //scale 0.8
}

//cadeiras
#declare i = 34;
#while (i < 55)
    union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> pigment {color Black}} 
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> pigment {color Black}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> pigment {color Black}}
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> pigment {color Black}}
        //encosto
        box {<-7.9, 0.3, 0.1>, <-8.1, 1.1, 1.6> pigment {color Blue}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Blue}}
        translate <i, 0, 21.5>
    } 
    #declare i = i + 10;
#end

#declare i = 34;
#while (i < 55)
    union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> pigment {color Black}} 
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> pigment {color Black}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> pigment {color Black}}
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> pigment {color Black}}
        //encosto
        box {<-7.9, 0.3, 0.1>, <-8.1, 1.1, 1.6> pigment {color Blue}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Blue}}
        translate <i, 0, 27.5>
    } 
    #declare i = i + 10;
#end
  
#declare i = 21.5;
#while (i < 42)
    union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> pigment {color Black}} 
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> pigment {color Black}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> pigment {color Black}}
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> pigment {color Black}}
        //encosto
        box {<-7.9, 0.3, 0.1>, <-8.1, 1.1, 1.6> pigment {color Blue}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Blue}}
        rotate y*180
        translate <i, 0, 23>
    }
    #declare i = i + 10;
#end

#declare i = 21.5;
#while (i < 42)
    union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> pigment {color Black}} 
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> pigment {color Black}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> pigment {color Black}}
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> pigment {color Black}}
        //encosto
        box {<-7.9, 0.3, 0.1>, <-8.1, 1.1, 1.6> pigment {color Blue}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Blue}}
        rotate y*180
        translate <i, 0, 29>
    }
    #declare i = i + 10;
#end
 
//mesa da mulher   
union {
    //topo
    box {<-8, 1, -3>, <-6, 1.15, 1> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.2>, <-7.1, 1.15, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, 1.2>, <-7.1, 1.15, 1> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.2>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 1.15, -3.2>, <-6, 1, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, 0.9>, <-6, -0.85, 1> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 1.15, 0.9>, <-6, 1, 1> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, -0.5, 1>, <-7.1, 1, -2.9> pigment {color Goldenrod}} 
    translate <8, 0, 0>
    rotate y*-85
    translate <16, 0, 40>
}

//mesa da mulher   
union {
    //topo
    box {<-8, 1, -3>, <-6, 1.15, 1> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.2>, <-7.1, 1.15, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, 1.2>, <-7.1, 1.15, 1> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.2>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 1.15, -3.2>, <-6, 1, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, 0.9>, <-6, -0.85, 1> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 1.15, 0.9>, <-6, 1, 1> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, -0.5, 1>, <-7.1, 1, -2.9> pigment {color Goldenrod}} 
    translate <8, 0, 0>
    rotate y*-105
    translate <20.5, 0, 40>
}

//mesa da mulher   
union {
    //topo
    box {<-8, 1, -3>, <-6, 1.15, 1> pigment {color Goldenrod}}
    //vertical
    box {<-6.9, -1, -3.2>, <-7.1, 1.15, -3> pigment {color Black} finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-6.9, -1, 1.2>, <-7.1, 1.15, 1> pigment {color Black}}
    //suporte de baixo horizontal
    box {<-8, -1, -3.2>, <-6, -0.85, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 1.15, -3.2>, <-6, 1, -3> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //suporte de cima horizontal
    box {<-8, -1, 0.9>, <-6, -0.85, 1> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    box {<-8, 1.15, 0.9>, <-6, 1, 1> pigment {color Black}finish{specular 0.3 roughness 0.02 diffuse 0.8 ambient 0}}
    //coisa em baixo da tampa
    box {<-6.9, -0.5, 1>, <-7.1, 1, -2.9> pigment {color Goldenrod}} 
    translate <8, 0, 0>
    rotate y*-85
    translate <7, 0, 40>
}
//cadeiras vermelhas
union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> texture {Chrome_Metal}}  
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> texture {Chrome_Metal}} 
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> texture {Chrome_Metal}} 
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> texture {Chrome_Metal}} 
        //encosto
        box {<-7.9, 0.6, 0.1>, <-8.1, 1.1, 1.6> pigment {color Red}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Red}}
        translate <8,0,0>
        rotate y*-90
        translate <16.5, 0, 38>
}

union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> texture {Chrome_Metal}}  
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> texture {Chrome_Metal}} 
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> texture {Chrome_Metal}} 
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> texture {Chrome_Metal}} 
        //encosto
        box {<-7.9, 0.6, 0.1>, <-8.1, 1.1, 1.6> pigment {color Red}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Red}}
        translate <8,0,0>
        rotate y*-90
        translate <18.5, 0, 38>
}

union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> texture {Chrome_Metal}}  
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> texture {Chrome_Metal}} 
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> texture {Chrome_Metal}} 
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> texture {Chrome_Metal}} 
        //encosto
        box {<-7.9, 0.6, 0.1>, <-8.1, 1.1, 1.6> pigment {color Red}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Red}}
        translate <8,0,0>
        rotate y*-95
        translate <9, 0, 38>
}

//armario
box {<-1.5, -1, 45>, <1, 5, 50> pigment {color Goldenrod}}

//mesa redonda
union {
    cylinder {<0,-1,0>, <0,0.8,0>, 0.07 pigment {color Black}}
    cylinder {<0,0.8,0>, <0,0.9,0>, 1.7 pigment {color Black}}
    box {<-0.1,-1,-0.1>, <0.1, -0.9, 1.2> pigment {color Black}}
    box {<-0.1,-1,-0.1>, <0.1, -0.9, -1.2> pigment {color Black}}
    box {<-0.1,-1,-0.1>, <1.2, -0.9, 0.1> pigment {color Black}}
    box {<-0.1,-1,-0.1>, <-1.2, -0.9, 0.1> pigment {color Black}} 
    translate <8.5,0,28> 
}

union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> texture {Chrome_Metal}}  
        box {<-8, -1, 1.2>, <-8.1, 1.1, 1.3> texture {Chrome_Metal}} 
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> texture {Chrome_Metal}} 
        box {<-7, -1, 1.2>, <-7.1, 0, 1.3> texture {Chrome_Metal}} 
        //encosto
        box {<-7.9, 0.6, 0.1>, <-8.0, 1.1, 1.3> pigment {color Red}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.1, 1.3> pigment {color Red}}
        translate <8,0,0>
        rotate y*-115
        translate <9.5, 0, 26>
}

union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> texture {Chrome_Metal}} 
        box {<-8, -1, 1.2>, <-8.1, 1.1, 1.3> texture {Chrome_Metal}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> texture {Chrome_Metal}}
        box {<-7, -1, 1.2>, <-7.1, 0, 1.3> texture {Chrome_Metal}}
        //encosto
        box {<-7.9, 0.6, 0.1>, <-8.0, 1.1, 1.3> pigment {color Red}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.1, 1.3> pigment {color Red}}
        translate <8,0,0>
        rotate y*-20
        translate <6.5, 0, 26>
}

union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> pigment {color Black}} 
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> pigment {color Black}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> pigment {color Black}}
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> pigment {color Black}}
        //encosto
        box {<-7.9, 0.3, 0.1>, <-8.1, 1.1, 1.6> pigment {color Blue}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Blue}}
        translate <68, 0, 21.5>
}
union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> pigment {color Black}} 
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> pigment {color Black}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> pigment {color Black}}
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> pigment {color Black}}
        //encosto
        box {<-7.9, 0.3, 0.1>, <-8.1, 1.1, 1.6> pigment {color Blue}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Blue}}
        translate <68, 0, 19>
}

union {
        //pes tras
        box {<-8, -1, 0>, <-8.1, 1.1, 0.1> pigment {color Black}} 
        box {<-8, -1, 1.5>, <-8.1, 1.1, 1.6> pigment {color Black}}
        //pes frente
        box {<-7, -1, 0>, <-7.1, 0, 0.1> pigment {color Black}}
        box {<-7, -1, 1.5>, <-7.1, 0, 1.6> pigment {color Black}}
        //encosto
        box {<-7.9, 0.3, 0.1>, <-8.1, 1.1, 1.6> pigment {color Blue}}
        //assento
        box {<-8.1, 0, 0>, <-7, 0.2, 1.5> pigment {color Blue}}
        translate <8,0,0>
        rotate y*-90
        translate <73, 0, 18>
}
        





