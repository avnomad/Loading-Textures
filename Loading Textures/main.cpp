//	Copyright (C) 2010-2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of Loading Textures.
 *
 *	Loading Textures is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	Loading Textures is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with Loading Textures.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gl/glew.h>
#include <gl/glut.h>
#include <cstdlib>

#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

GLuint textures[4];


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.0,0.5,0.0);


	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,1.0);
		glVertex2d(-0.975,-0.975);
		glTexCoord2f(1.0,1.0);
		glVertex2d(-0.025,-0.975);
		glTexCoord2f(1.0,0.0);
		glVertex2d(-0.025,-0.025);
		glTexCoord2f(0.0,0.0);
		glVertex2d(-0.975,-0.025);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textures[1]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,1.0);
		glVertex2d(0.025,-0.975);
		glTexCoord2f(1.0,1.0);
		glVertex2d(0.975,-0.975);
		glTexCoord2f(1.0,0.0);
		glVertex2d(0.975,-0.025);
		glTexCoord2f(0.0,0.0);
		glVertex2d(0.025,-0.025);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textures[2]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,1.0);
		glVertex2d(0.025,0.025);
		glTexCoord2f(1.0,1.0);
		glVertex2d(0.975,0.025);
		glTexCoord2f(1.0,0.0);
		glVertex2d(0.975,0.975);
		glTexCoord2f(0.0,0.0);
		glVertex2d(0.025,0.975);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,textures[3]);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0,1.0);
		glVertex2d(-0.975,0.025);
		glTexCoord2f(1.0,1.0);
		glVertex2d(-0.025,0.025);
		glTexCoord2f(1.0,0.0);
		glVertex2d(-0.025,0.975);
		glTexCoord2f(0.0,0.0);
		glVertex2d(-0.975,0.975);
	glEnd();


	glutSwapBuffers();
} // end function display


void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 27:	// escape key
		exit(0);
	} // end switch
} // end function keyboard


void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
} // end function reshape


#include <fstream>
using std::ifstream;
#include <cctype>

GLubyte *load_image(const char *file_name,GLint &width,GLint &height)
{
	ifstream in(file_name,ifstream::in | ifstream::binary);
	int maxVal;
	int bytes = 1;
	GLubyte *image;
	int ch;

	if(!in)
		cerr << "\aCannot open file!" << endl;

	if(in.get() != 'P' || in.get() != '6')
		cerr << "\aInvalid file format!" << endl;

	/* irfanwiew ppms */
	while(isspace(ch = in.get()))
		;
	if(ch == '#')
		while(in.get() != '\n')
			;
	else
		in.unget();
	/* end irfanwiew ppms */

	in >> width >> height >> maxVal;
	if(maxVal <= 0 || maxVal >= 65536)
		cerr << "\aFile corrupted!" << endl;
	
	if(maxVal >= 256)
		bytes = 2;

	in.ignore();	// 1 whitespace character before data.

	image = new GLubyte[width*height*bytes*3];
	in.read((char*)image,width*height*bytes*3);

	return image;
} // end function load_image





int main(int argc, char **argv)
{
	// glut initialization
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(320,320);
	glutInitWindowPosition(800,160);
	glutCreateWindow("Loading Textures");

	// glew initialization
	glewInit();

	// OpenGL initialization
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(4,textures);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	GLubyte *image;
	GLint width,height;

	image = load_image("ppm/1.ppm",width,height);
	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	delete[] image;

	image = load_image("ppm/2.ppm",width,height);
	glBindTexture(GL_TEXTURE_2D,textures[1]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	delete[] image;

	image = load_image("ppm/3.ppm",width,height);
	glBindTexture(GL_TEXTURE_2D,textures[2]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	delete[] image;

	image = load_image("ppm/4.ppm",width,height);
	glBindTexture(GL_TEXTURE_2D,textures[3]);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	delete[] image;


	// event handling initialization
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
} // end function main
