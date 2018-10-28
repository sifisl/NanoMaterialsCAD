#pragma once

#define len 200
#define fontmapwidht 512
#define fontmapheight 512
#define Angstrom -1
#define one_bar -2
#define two_bar -3
#define noadv false

ifstream font;
void openfont(char* f)
{
	font.open(f);

}

void closefont()
{
	font.close();
}
void JGN_StrokeCharacter(char c, bool hadv = true)
{
	char line[len];
	char* token;
	bool done = false;
	float x, y, w, h, adv;
	if (c == 0)
	{
		return;
	}
	else if (c == Angstrom)
	{
		JGN_StrokeCharacter('A');
		glTranslatef(-0.068, 0.082, 0);
		glScalef(0.5, 0.5, 0.5);
		JGN_StrokeCharacter('o', noadv);
		glScalef(2, 2, 2);
		glTranslatef(0.068, -0.082, 0);


		return;
	}
	else if (c == one_bar)
	{
		glTranslatef(0, 0.1, 0);
		JGN_StrokeCharacter('-',noadv);
		glTranslatef(0, -0.1, 0);
		JGN_StrokeCharacter('1');
		
		return;
	}
	else if (c == two_bar)
	{
		glTranslatef(0, 0.1, 0);
		JGN_StrokeCharacter('-',noadv);
		glTranslatef(0, -0.1, 0);
		JGN_StrokeCharacter('2');
		
		return;
	}
	///////////////////////
	while (!done)
	{
		font.getline(line, len);
		token = strtok(line, "=");
		token = strtok(NULL, " \t");
		
		if (atoi(token) == (int)c)
		{
			
			done = true;

			token = strtok(NULL, "=");
			token = strtok(NULL, " \t");
			cout << token << endl;
			x = jgn::atof(token) / fontmapwidht;
			
			token = strtok(NULL, "=");
			token = strtok(NULL, " \t");
			y = (512 - jgn::atof(token)) / fontmapheight;

			token = strtok(NULL, "=");
			token = strtok(NULL, " \t");
			w = jgn::atof(token) / fontmapwidht;

			token = strtok(NULL, "=");
			token = strtok(NULL, " \t");
			h = jgn::atof(token) / fontmapheight;

			token = strtok(NULL, "=");
			token = strtok(NULL, " \t");
			token = strtok(NULL, "=");
			token = strtok(NULL, " \t");
			token = strtok(NULL, "=");
			token = strtok(NULL, " \t");
			adv = jgn::atof(token) / fontmapwidht;

			glEnable(GL_TEXTURE_2D);
			glBegin(GL_QUADS);

			glTexCoord2d(x, y);
			glVertex2d(0, h);

			glTexCoord2d(x + w, y);
			glVertex2d(w, h);

			glTexCoord2d(x + w, y - h);
			glVertex2d(w, 0);

			glTexCoord2d(x, y - h);
			glVertex2d(0, 0);

			glEnd();
			glDisable(GL_TEXTURE_2D);
			if(hadv)
				glTranslatef(adv, 0, 0);

		}
	}
	font.clear();
	font.seekg(0);
}