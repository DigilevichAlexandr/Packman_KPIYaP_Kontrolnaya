#include "Borders.h"

SDL_Rect* Borders::MakeBorders()
{
	SDL_Rect* borders =new SDL_Rect[55];

	borders[0].x = 0;
	borders[0].y = 0;
	borders[0].w = 444;
	borders[0].h = 7;

	borders[1].x = 211;
	borders[1].y = 7;
	borders[1].w = 20;
	borders[1].h = 55;

	borders[2].x = 0;
	borders[2].y = 8;
	borders[2].w = 9;
	borders[2].h = 132;

	borders[3].x = 35;
	borders[3].y = 35;
	borders[3].w = 53;
	borders[3].h = 29;

	borders[4].x = 116;
	borders[4].y = 35;
	borders[4].w = 68;
	borders[4].h = 29;

	borders[5].x = 259;
	borders[5].y = 35;
	borders[5].w = 69;
	borders[5].h = 29;

	borders[6].x = 357;
	borders[6].y = 35;
	borders[6].w = 52;
	borders[6].h = 29;

	borders[7].x = 436;
	borders[7].y = 7;
	borders[7].w = 8;
	borders[7].h = 125;

	borders[8].x = 34;
	borders[8].y = 90;
	borders[8].w = 54;
	borders[8].h = 14;

	borders[9].x = 163;
	borders[9].y = 90; 
	borders[9].w = 116;
	borders[9].h = 14;

	borders[10].x = 211;
	borders[10].y = 104;
	borders[10].w = 20;
	borders[10].h = 42;

	borders[11].x = 356;
	borders[11].y = 90;
	borders[11].w = 52;
	borders[11].h = 14;

	borders[12].x = 116;
	borders[12].y = 90;
	borders[12].w = 19;
	borders[12].h = 98;

	borders[13].x = 7;
	borders[13].y = 132;
	borders[13].w = 81;
	borders[13].h = 7;

	borders[14].x = 135;
	borders[14].y = 133;
	borders[14].w = 48;
	borders[14].h = 14;

	borders[15].x = 259;
	borders[15].y = 133;
	borders[15].w = 48;
	borders[15].h = 14;

	borders[16].x = 307;
	borders[16].y = 91;
	borders[16].w = 20;
	borders[16].h = 98;

	borders[17].x = 356;
	borders[17].y = 132;
	borders[17].w = 79;
	borders[17].h = 7;

	borders[18].x = 81;
	borders[18].y = 138;
	borders[18].w = 7;
	borders[18].h = 50;

	borders[19].x = 0;
	borders[19].y = 182;
	borders[19].w = 81;
	borders[19].h = 7;

	borders[20].x = 163;
	borders[20].y = 174;
	borders[20].w = 44;
	borders[20].h = 7;

	borders[21].x = 236;
	borders[21].y = 174;
	borders[21].w = 43;
	borders[21].h = 7;

	borders[22].x = 355;
	borders[22].y = 132;
	borders[22].w = 7;
	borders[22].h = 56;

	borders[23].x = 361;
	borders[23].y = 182;
	borders[23].w = 82;
	borders[23].h = 7;

	borders[24].x = 0;
	borders[24].y = 217;
	borders[24].w = 88;
	borders[24].h = 7;

	borders[25].x = 81;
	borders[25].y = 222;
	borders[25].w = 7;
	borders[25].h = 50;

	borders[26].x = 115;
	borders[26].y = 216;
	borders[26].w = 19;
	borders[26].h = 56;

	borders[27].x = 163;
	borders[27].y = 181;
	borders[27].w = 7;
	borders[27].h = 49;

	borders[28].x = 170;
	borders[28].y = 224;
	borders[28].w = 110;
	borders[28].h = 7;

	borders[29].x = 164;
	borders[29].y = 258;
	borders[29].w = 116;
	borders[29].h = 14;

	borders[30].x = 307;
	borders[30].y = 216;
	borders[30].w = 20;
	borders[30].h = 56;

	borders[31].x = 356;
	borders[31].y = 216;
	borders[31].w = 88;
	borders[31].h = 7;

	borders[32].x = 355;
	borders[32].y = 223;
	borders[32].w = 7;
	borders[32].h = 49;

	borders[33].x = 362;
	borders[33].y = 266;
	borders[33].w = 82;
	borders[33].h = 7;

	borders[34].x = 0;
	borders[34].y = 266;
	borders[34].w = 88;
	borders[34].h = 7;

	borders[35].x = 211;
	borders[35].y = 272;
	borders[35].w = 21;
	borders[35].h = 43;

	borders[36].x = 0;
	borders[36].y = 273;
	borders[36].w = 7;
	borders[36].h = 171;

	borders[37].x = 36;
	borders[37].y = 300;
	borders[37].w = 52;
	borders[37].h = 14;

	borders[38].x = 67;
	borders[38].y = 314;
	borders[38].w = 20;
	borders[38].h = 42;

	borders[39].x = 115;
	borders[39].y = 300;
	borders[39].w = 69;
	borders[39].h = 14;

	borders[40].x = 7;
	borders[40].y = 343;
	borders[40].w = 33;
	borders[40].h = 14;

	borders[41].x = 115;
	borders[41].y = 343;
	borders[41].w = 20;
	borders[41].h = 42;

	borders[42].x = 35;
	borders[42].y = 385;
	borders[42].w = 149;
	borders[42].h = 14;

	borders[43].x = 163;
	borders[43].y = 342;
	borders[43].w = 117;
	borders[43].h = 14;

	borders[44].x = 212;
	borders[44].y = 356;
	borders[44].w = 20;
	borders[44].h = 42;

	borders[45].x = 259;
	borders[45].y = 300;
	borders[45].w = 68;
	borders[45].h = 14;

	borders[46].x = 307;
	borders[46].y = 343;
	borders[46].w = 20;
	borders[46].h = 41;

	borders[47].x = 260;
	borders[47].y = 385;
	borders[47].w = 147;
	borders[47].h = 14;

	borders[48].x = 356;
	borders[48].y = 300;
	borders[48].w = 20;
	borders[48].h = 57;

	borders[49].x = 375;
	borders[49].y = 300;
	borders[49].w = 32;
	borders[49].h = 14;

	borders[50].x = 404;
	borders[50].y = 342;
	borders[50].w = 38;
	borders[50].h = 14;

	borders[51].x = 435;
	borders[51].y = 273;
	borders[51].w = 7;
	borders[51].h = 164;

	borders[52].x = 7;
	borders[52].y = 437;
	borders[52].w = 429;
	borders[52].h = 7;

	borders[53].x = 273;
	borders[53].y = 180;
	borders[53].w = 7;
	borders[53].h = 44;
		
	borders[54].x = 0;
	borders[54].y = 0;
	borders[54].w = 0;
	borders[54].h = 0;

	return borders;
}