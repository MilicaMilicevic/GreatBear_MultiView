#include<gl\glut.h>

const GLint screenWidth=350,screenHeigth=350;

const GLfloat BLACK[]={0,0,0},RED[]={1,0,0},BLUE[]={0,0,1},GREEN[]={0,1,0}; //boje koje cemo koristiti

//postavke
void init(){
	glClearColor(1.0,1.0,1.0,0.0); //white background, setujemo, ali je jos uvijek nema
	glMatrixMode(GL_PROJECTION);
	glPointSize(5.0);
	glLoadIdentity();
	gluOrtho2D(0,(GLdouble)screenWidth,0,(GLdouble)screenHeigth);
}

void defineStars(){ //modularizacija!
		glVertex2f(289,190);
		glVertex2f(320,128);
		glVertex2f(239,67);
		glVertex2f(194,101);
		glVertex2f(129,83);
		glVertex2f(75,73);
		glVertex2f(20,10);
}

void displayStars(const GLfloat color[]){
	glColor3fv(color);
	glBegin(GL_POINTS);			
		defineStars();
	glEnd();
	glFlush();
}

void connectStars(const GLfloat color[]){
	glColor3fv(color);
	glBegin(GL_LINE_STRIP);
		defineStars();
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(289,190);
		glVertex2f(194,101);
	glEnd();
	displayStars(color); //zelimo i da su tacke uocljive!!!
	glFlush();
}

void baseDisplay(){
	glClear(GL_COLOR_BUFFER_BIT); //crta od gornje lijeve cetvrtine
	glViewport(0,(GLsizei)screenHeigth/2,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	connectStars(BLUE);
	glViewport((GLsizei)screenWidth/2,(GLsizei)screenHeigth/2,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	connectStars(BLACK); //crta gornju desnu
	glViewport(0,0,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	connectStars(RED); //donja lijeva
	glViewport((GLsizei)screenWidth/2,0,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	connectStars(GREEN);
}


void secondDisplay(){
	glClear(GL_COLOR_BUFFER_BIT); 
	glViewport(0,(GLsizei)screenHeigth/2,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	displayStars(BLUE);
	glViewport((GLsizei)screenWidth/2,(GLsizei)screenHeigth/2,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	connectStars(BLACK); 
	glViewport(0,0,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	displayStars(RED); 
	glViewport((GLsizei)screenWidth/2,0,(GLsizei)screenWidth/2,(GLsizei)screenHeigth/2);
	connectStars(GREEN);
}

//keyboard callback
void keyboard(unsigned char key, int x,int y){
	switch(key){
				case 'p': //postavka primarnog prikaza
					baseDisplay();
					break;
				case 'd': //prva dva nisu konektovana
					secondDisplay();
					break;
				case 'e': //brisanje prikaza
					glClear(GL_COLOR_BUFFER_BIT);
					break;
				case 27: //ESC taster
					exit(0);	
			}
	glFlush();
}

int main(int argc,char** argv){
	glutInit(&argc,argv); 
	glutInitWindowSize(screenWidth,screenHeigth);
	glutCreateWindow("Great Bear Multiview");
	init(); //pocetna scena!
	glutDisplayFunc(baseDisplay);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}