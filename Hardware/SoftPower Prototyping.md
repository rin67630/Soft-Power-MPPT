# Instructions to build the prototype

these are the instructions to build the INA3221 based prototype.  
We will start with a 5x7 CM prototyping board.  
The first thing will be to drill the fixation holes to 3,2mm. The corners will break, but that does not matter.

## Preparing the INA3221:
![image](https://user-images.githubusercontent.com/14197155/105363457-57ed7c80-5bfc-11eb-8481-f62d0aa3a43a.png)  
The 0.1 Ohm SMD shunt resistors will enable measurement up to 0.8Amps only, which is okay for a 10W panel.  
For bigger panels you need to replace the SMD shunt resistors with 0.01 Ohm models. Do not worry, replacing these kind of resistance is not rocket science.
Just put a good quantity of solder tin on the terminals and heat in short sequence both sides, then quickly shift away the SMD resitor with the tip of your iron.
You can do that! I could also, and I am an old man, not very far from getting Parkinson.
Then position the new resistor inplace and solder first one side, while you hold the item, then solder the other side with enough tin, and come back to the first side with fresh tin.

Then we will solder the screw terminals. I had two- and three- blocks available, which will allow me to place the ground terminals beneath the respective positive terminals, which is a somewhat more logical disposition. On the top side of the INA module, I am usually soldering a strong wire bridge between the 2 GND holes, useful to clamp the GND of a multimeter.  
If you only have 2-blocks, you can solder them directly onto the GND holes.   
![image](https://user-images.githubusercontent.com/14197155/105363334-34c2cd00-5bfc-11eb-903b-07b1305c283d.png)
Then solder the 8 pins on the INA module and then on the top line of the prototyping board between the rows H to Q. 


## Preparing the "Fine Red" 5V buck converter.  
The "Fine Red" buck converter fits ideally under the Wemos D1 and delivers a 5V USB plug, situated just under the USB connector of the WEMOS-D1:  
![image](https://user-images.githubusercontent.com/14197155/105381085-ea971700-5c0e-11eb-9fde-c156cdf54698.png)  
To solder this module on the prototyping board, we will use a direct solder connection between the two boards.  
First of all you need to prepare the module, which back should be as flat as possible.  
Cut the pads from the USB connector with a cutting plyer as flat as possible.  
Then put a generous quantity of solder tin on the outside USB connections:
![image](https://user-images.githubusercontent.com/14197155/105383836-d9033e80-5c11-11eb-89be-c0c5d75c8b2a.png)  
Solder a provisional wire bridge on the input ports leaving 1cm wire in excess at the other side.  
![image](https://user-images.githubusercontent.com/14197155/105382180-18c92680-5c10-11eb-8000-5b24a8c58c94.png)  
Place the converter on the prototyping board in such a way is that these wires fit into the holes J-09 and O-09, solder these two holes.  
![image](https://user-images.githubusercontent.com/14197155/105382587-8412f880-5c10-11eb-87e8-bf3ca48f67fc.png)  
Then the two outside USB connections should be exactly under the holes K-03 and N-03. Press firmly the two boards together and fill these two holes generously with tin so the molten tin will contact through the red board.
The two boards should now be firmly connected together. 
You can then cut the wire bridge at the other side and test your connections: 
If you suply 12V, (+ to O-09 and - to J-09), you should get 5V (+ at N-03 and - at K-03). 

## Preparing the HW813 buck converter under the Wemos.  
if you choose to use HW813 buck converters instead...
( I am currently waiting for a new batch of HW813 to come, so I can provide pictures and description in time) 

## Preparing the Wemos connectors.
Solder the female short pin connectors between H02 to H09 and between Q-02 and Q-09.
Solder the female long pin connectors through the Wemos D1. you can then plug the WomosD1 onto the board:  
![image](https://user-images.githubusercontent.com/14197155/105387729-208bc980-5c16-11eb-9954-28ac80c3b4aa.png)  



...to be continued.
