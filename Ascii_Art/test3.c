#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window*window = NULL;
SDL_Surface*surfacescreen = NULL;
//main page images
SDL_Surface *imagesurf1= NULL;
SDL_Surface *imagesurf2 = NULL;
SDL_Surface *imagesurf3 = NULL;
//buttons
SDL_Surface *imagesurfb1= NULL;
SDL_Surface *imagesurfb2= NULL;
SDL_Surface *imagesurfb3= NULL;
//titles
SDL_Surface *titlesurface= NULL;
//textsurfaces
SDL_Surface *text_surface=NULL;
SDL_Surface *notesurface=NULL;
//drawing part
SDL_Surface *testpresentsurface = NULL;

//fonts
TTF_Font*font;
TTF_Font*fonta;
TTF_Font*font2;
//prototype
void mainface();
void mainbutton();
void background();
void asciitable();
void note();
void charactertablebrightness();
//global variables
int brightnesscal(SDL_Surface*surface,int sw, int sh,int w,int h);
int windowwidth=800;
int windowheight=640;
int subwidth=8;
int subheight=8;
int x,y,asn;
int i;
int min;
//tables
char ascii[100]; 
int charbrightntable[100];	
int imagebrightnesstable1[32000];
int minntable[100000];





typedef
struct
RGBcolour
{
Uint8 r;
Uint8 g;
Uint8 b;
} 
RGBcolour;


int main(int argc, char *argv[])
{
	//initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
	{
	 printf("error:%s \n", SDL_GetError());
	 return 1;
	}
	
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	//load font
	font=TTF_OpenFont("font1.ttf", 10);
	/*source from Eike'slecture 15 starts here       https://brightspace.bournemouth.ac.uk/d2l/le/content/13401/viewContent/53598/View*/
	//Create a window
	window = SDL_CreateWindow("Window", 200,150,800,640,SDL_WINDOW_SHOWN);
	/*source from Eike'slecture 15 ends here*/
	/*code from lazyfoo website starts here http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php */
	if(window == NULL)
	{
		printf("Window could not be created! SDL_Error:%s\n", SDL_GetError());
		return 0 ;
	}
	/*code from lazyfoo website ends here http://lazyfoo.net/tutorials/SDL/01_hello_SDL/index2.php */
	else
	{         
		//set the cover by calling functions
		background();
		mainface();
		mainbutton();
	}
		  
	int finished=0;
	SDL_Event event;
	while (!finished)
	{
		
		while( SDL_PollEvent(&event) )
		{
			switch(event.type)
			{
				 case SDL_QUIT:
					
						finished=1;
					
					break;
						
				 case SDL_MOUSEBUTTONDOWN:
				 {
					/*get help base on New D.I.C Head starts here       http://www.dreamincode.net/forums/topic/175010-creating-buttonsmenus-in-sdl/*/
					int x=event.motion.x;
					int y=event.motion.y;
					
					SDL_Rect stretchRect;
					stretchRect.x=0;
					stretchRect.y=0;
					stretchRect.w=800;
					stretchRect.h=640;
						
					if((x>380)&&(x<440)&&(y>190)&&(y<220))
					{
						//strecth first picture to fullscreen
						printf("Clicked on button 1\n");
						SDL_BlitScaled( imagesurf1, NULL, surfacescreen, &stretchRect);
						SDL_FreeSurface(imagesurf1);
						note();
					}
					if((x>380)&&(x<440)&&(y>400)&&(y<430))
					{
						//strecth second picture to fullscreen
						printf("Clicked on button 2\n");
						SDL_BlitScaled( imagesurf3, NULL, surfacescreen, &stretchRect);
						SDL_FreeSurface(imagesurf2);
						note();
					}
					if((x>380)&&(x<440)&&(y>600)&&(y<630))
					{
						//strecth last picture to fullscreen
						printf("Clicked on button 3\n ");
						SDL_BlitScaled( imagesurf2, NULL, surfacescreen, &stretchRect);
						SDL_FreeSurface(imagesurf2);
						note();
					}
					
					SDL_UpdateWindowSurface(window);
				}
				/*get help base on  New D.I.C Head ends here       http://www.dreamincode.net/forums/topic/175010-creating-buttonsmenus-in-sdl/*/
					break;
				
				case SDL_KEYDOWN:
				{		
					switch( event.key.keysym.sym )
					{
						 case SDLK_ESCAPE: 
							{
								finished=1;
							 
							}
                          
						case SDLK_BACKSPACE:
							{
								//go back to the cover
								printf("Clicked on backspace\n");
								SDL_FreeSurface(surfacescreen);
								background();
								mainface();
								mainbutton();		
							}
							break;
							
						case SDLK_g:
							{
								printf("g is pressed,please wait for the calculation\n");
								//start calculate
								//calculate image brightness with small subs
								for (x=0,i=0;x<windowwidth;x+=subwidth)
								{
									for (y=0; y<windowheight;y+=subheight)
									{
										
										int subb=brightnesscal(surfacescreen,x,y,x+subwidth,y+subheight);
										imagebrightnesstable1[i]= subb;
										i++;
									}
									
								}
								
								printf("image brightness calculation is finished,please wait\n");
								//load ascii brightness
								fonta=TTF_OpenFont("font1.ttf", 800);
								int amax=255;
								int amin=167;
								//load ascii table
								/* source from my classmate YiYun Hu starts here*/
								int t;
								char d;
								for( t=0,x=32;x<127;t++,x++)
								{
									d=(char)x;
									ascii[t]=d;
								}
								/* source from my classmate YiYun Hu ends here*/
									
								//chracter brightness calculation
								for(i=0;i<95;i++)
								{
									
									char temp[2];
									temp[0]=ascii[i];
									temp[1]='\0';
									SDL_Color color={0,0,0};
									SDL_Surface *text_surface=TTF_RenderText_Solid(fonta,temp,color);
									SDL_Rect stretchRect4; 
									stretchRect4.x=150;
									stretchRect4.y=-160;
									stretchRect4.w=640;
									stretchRect4.h=400;
									SDL_BlitSurface(text_surface, NULL, surfacescreen, &stretchRect4);
									//set calculated brightness into array
									int charbrightn;
									charbrightn =brightnesscal(text_surface,0,0,800,640);
									int can=(255*(charbrightn-amin))/(amax-amin);
									charbrightntable[i] = can;
									SDL_FreeSurface(text_surface);
									
								}
								printf("ascii brightness is ready please keep waiting\n");
								//compare the character brightness and the image sub brightness
								int b,minn,diff,a;
								for(a=0,i=0;a<(windowwidth*windowheight)/(subwidth*subheight);a++)
								{
									int min = abs(imagebrightnesstable1[a]-charbrightntable[0]);
									for(b=0;b<100;b++)
									{
										diff =abs(imagebrightnesstable1[a]-charbrightntable[b]);
										if(diff<min)
										{
											min=diff;
											minn=b;
										}
									}
									minntable[i]=minn;		
									i++; 	
								}	
								printf("compart is finished,it is almost done!\n"); 
								//refill surface with user input color and get the font color
								surfacescreen = SDL_GetWindowSurface(window);
								SDL_Rect bg;
								bg.x = 0;
								bg.y = 0;
								bg.w = 800;
								bg.h = 640;
								int rv,gv,bv,fr,fg,fb;;
								printf("pleae input the rgb colour u want for the background and font:");
								scanf("%d,%d,%d,%d,%d,%d\n",&rv, &gv, &bv,&fr, &fg, &fb);
								fflush(stdin);
								SDL_Color color={fr,fg,fb};
								SDL_FillRect(surfacescreen, &bg, SDL_MapRGB(surfacescreen->format, rv, gv, bv));
								SDL_UpdateWindowSurface(window);
								font=TTF_OpenFont("font1.ttf", 8);
								//present final shot on window
								for(x=0,i=0;x<windowwidth;x+=subwidth)
								{
									for(y=0;y<windowheight;y+=subheight)
									{
										asn=minntable[i];
										char temp[2];
										temp[0]=ascii[asn];
										temp[1]='\0';
										testpresentsurface=TTF_RenderText_Solid(font,temp,color);
										SDL_Rect stretchRect4;
										stretchRect4.x=x;
										stretchRect4.y=y;
										stretchRect4.w=subwidth;
										stretchRect4.h=subheight;
										SDL_BlitSurface(testpresentsurface, NULL, surfacescreen, &stretchRect4);
										SDL_UpdateWindowSurface(window);	
										i++;
									}
								}
								printf("present finished!\npress s for saving your work!\n");
							}
							break;
							
						case SDLK_s:
							{
								printf("S is pressed\n");
								//save result surface as bmp with a user input name
								char str1[20];
								printf("Please Enter name for picture(it should be less than 20 characters):");
								scanf("%s",str1);
								SDL_SaveBMP(surfacescreen,str1);	
								if(str1[1])
								{
									printf("The picture is saved!\n");	
								}
								for(i=0;i<20;i++)
								{
									str1[i]='\0';
									
								}
							}
							break;
							
						default:
							break;
					}
				}
					break;
				/*source from Cos starts here*/
				case SDL_KEYUP:
					break;
			}																		
		}/*source from Cos ends here*/
	}   
	SDL_DestroyWindow(window);
	TTF_CloseFont(font);
	TTF_CloseFont(font2);
	TTF_CloseFont(fonta);
	TTF_Quit();
	SDL_Quit();
}

void background()
{
	surfacescreen = SDL_GetWindowSurface(window);
	//background color
	SDL_Rect bg;
	bg.x = 0;
	bg.y = 0;
	bg.w = 800;
	bg.h = 640;
	SDL_FillRect(surfacescreen, &bg, SDL_MapRGB(surfacescreen->format, 200, 100, 100));
}
		 
void mainbutton()
{
	/* get help base on lazy foo website starts here http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php*/
	imagesurfb1=IMG_Load("button.bmp");
	imagesurfb2=IMG_Load("button.bmp");
	imagesurfb3=IMG_Load("button.bmp");		
	//firt button
	SDL_Rect stretchRectb1; 
    stretchRectb1.x = 380; 
    stretchRectb1.y = 190; 
    stretchRectb1.w = 60; 
    stretchRectb1.h = 30; 
    SDL_BlitScaled( imagesurfb1, NULL, surfacescreen, &stretchRectb1);
    //second button
    SDL_Rect stretchRectb2; 
    stretchRectb2.x = 380; 
    stretchRectb2.y = 400; 
    stretchRectb2.w = 60; 
    stretchRectb2.h = 30; 
    SDL_BlitScaled( imagesurfb2, NULL, surfacescreen, &stretchRectb2);
    //third button
    SDL_Rect stretchRectb3; 
    stretchRectb3.x = 380; 
    stretchRectb3.y = 600; 
    stretchRectb3.w = 60; 
    stretchRectb3.h = 30; 
    SDL_BlitScaled( imagesurfb3, NULL, surfacescreen, &stretchRectb3);
     /* get help base on lazy foo website ends here http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php*/
    SDL_UpdateWindowSurface(window);
    SDL_FreeSurface(imagesurfb1);
	SDL_FreeSurface(imagesurfb2);
	SDL_FreeSurface(imagesurfb3);
}
		     
void mainface()
{
	        
		     /* get help base on lazy foo website starts here http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php*/
		     //button surface rect fill
		     //load a image
		     imagesurf1=IMG_Load("a.tif");
		     //load b image 
		     imagesurf2=IMG_Load("b.jpg");
		     //load c image
		     imagesurf3=IMG_Load("c.jpg");
		      //strecha
		     SDL_Rect stretchRect1; 
		     stretchRect1.x = 10; 
		     stretchRect1.y = 10; 
		     stretchRect1.w = 300; 
		     stretchRect1.h = 200; 
		     //strechb
		     SDL_Rect stretchRect2; 
		     stretchRect2.x = 10;
		     stretchRect2.y = 430;
		     stretchRect2.w = 300; 
		     stretchRect2.h = 200; 
		     //strechc
		     SDL_Rect stretchRect3;
		     stretchRect3.x=10;
		     stretchRect3.y=220;
		     stretchRect3.w=300;
		     stretchRect3.h=200;
		     SDL_BlitScaled( imagesurf1, NULL, surfacescreen, &stretchRect1);
		     SDL_BlitScaled( imagesurf2, NULL, surfacescreen, &stretchRect2);
		     SDL_BlitScaled( imagesurf3, NULL, surfacescreen, &stretchRect3);
		      /* get help base on lazy foo website ends here http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php*/
		     
		     //Title
		     TTF_Init();
			 font=TTF_OpenFont("font1.ttf", 80);
			 SDL_Color color={100,0,0};
			 char title[20]="ASCII ART";
			 titlesurface=TTF_RenderText_Solid(font,title,color);
			 SDL_Rect stretchRect4;
			 stretchRect4.x=400;
			 stretchRect4.y=300;
			 stretchRect4.w=800;
			 stretchRect4.h=640;
			 SDL_BlitSurface(titlesurface, NULL, surfacescreen, &stretchRect4);
			 SDL_UpdateWindowSurface(window);
			 SDL_FreeSurface(titlesurface);	

		 }

void note()
{   
	//note for each image
	font2=TTF_OpenFont("font2.ttf", 20);
    SDL_Color color={255,255,255};
    notesurface=TTF_RenderText_Solid(font2,"Please press blackspace to go back and press g for ascii art",color);
    SDL_Rect stretchRect4;
	stretchRect4.x=0;
	stretchRect4.y=0;
    stretchRect4.w=640;
	stretchRect4.h=480;
    SDL_BlitSurface(notesurface, NULL, surfacescreen, &stretchRect4);
    SDL_UpdateWindowSurface(window);
}
																	
																	
int brightnesscal(SDL_Surface*surface,int sw, int sh,int w,int h)
{
	/*get help base on gigi labe website starts here http://gigi.nullneuron.net/gigilabs/converting-an-image-to-grayscale-using-sdl2/*/
	SDL_Surface*imagesurfp=SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
	Uint32 *pixels = (Uint32*)imagesurfp->pixels;
	/*get help base on gigi labe website ends here */
	int wholebrightness=0;
	int averagebrightness;
	int y,x;
	for (y = sh; y < h; y++)
	{
		for (x = sw; x < w; x++)
		{
			/*get source from gigi labe website starts here http://gigi.nullneuron.net/gigilabs/converting-an-image-to-grayscale-using-sdl2/*/
			Uint32 pixel = pixels[y * imagesurfp->w + x];
			Uint8 r = pixel >> 16 & 0xFF;
			Uint8 g = pixel >> 8 & 0xFF;
			Uint8 b = pixel & 0xFF;
			Uint8 brightnessp=0.212671f*r+0.715160f*g+0.072169f*b;
			/*get source from gigi labe website ends here */
			wholebrightness+=brightnessp;
			averagebrightness=wholebrightness/((w-sw)*(h-sh));
		}
	}
	return averagebrightness;														
}	

