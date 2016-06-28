#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

struct Vector
{
	float x, y, z;
public:
	Vector(float xC, float yC, float zC)
	{
		x = xC;
		y = yC;
		z = zC;
	}
};
typedef struct
{
	int Valid;                                                              //0x0
	char _0x0004[0x8];                              //0x4
	char Name[16];                                  //0xC
	int Team;                                                               //0x1C
	char _0x0020[0x4];                              //0x20
	int Rank;                                                               //0x24
	char _0x0028[0x10];                     //0x28
	int Perk;                                                               //0x38
	char _0x003C[0x8];                              //0x3C
	int Score;                                                      //0x44
	char _0x0048[0x458];                    //0x48
	int Attacking;                                          //0x4A0
	char _0x04A4[0x4];                              //0x4A4
	int Zooming;                                            //0x4A8
	char _0x04AC[0xB8];                     //0x4AC
}ClientInfo_T;

typedef struct
{
	char _0x0000[0x8];                       //0x0
	int Width;                                     //0x8
	int Height;                                    //0xC
	int FovX;                                      //0x10
	int FovY;                                      //0x14
	Vector Origin;                             //0x18
	Vector ViewAngles;                //0x24
	char _0x0048[0x24];                    //0x48
	float ZoomProgress;                     //0x6C
	char _0x0070[0x4ABC];              //0x70
	float RefViewAngleY;                 //0x4B2C
	float RefViewAngleX;                 //0x4B30
	char _0x4B34[0x34];                   //0x4B34
	float WeaponViewAngleX;         //0x4B68
	float WeaponViewAngleY;         //0x4B6C
}RefDef_T;

typedef struct
{
	float Recoil[3];                                   //0x0
	float Origin[3];                                   //0xC
	char _0x0018[0x80];                          //0x18
	float ViewAngleY;                             //0x98
	float ViewAngleX;                             //0x9C
}viewmatrix_t;

typedef struct
{
	char _0x0000[0x2];                         //0x0
	short Valid;                                     //0x2
	char _0x0004[0x10];                      //0x4
	float Origin[3];                              //0x14
	float Angles[3];                              //0x20
	char _0x002C[0x3C];                    //0x2C
	int Flags;                                       //0x68
	char _0x006C[0xC];                     //0x6C
	float OldOrigin[3];                       //0x78
	char _0x0084[0x18];                    //0x84
	float OldAngles[3];                      //0x9C
	char _0x00A8[0x28];                   //0xA8
	int ClientNumber;                       //0xD0
	short Type;                                  //0xD4
	char _0x00D6[0x12];                  //0xD6
	float NewOrigin[3];                    //0xE8
	char _0x00F4[0x1C];                  //0xF4
	float NewAngles[3];                    //0x110
	char _0x011C[0x7C];                 //0x11C
										//     	byte WeaponID;               //0x198
	char _0x0199[0x37];                  //0x199
	int IsAlive;                                  //0x1D0
	char _0x01D4[0x24];                 //0x1D4
}Entity_T;

typedef struct
{
	int ServerTime;                                 //0x0
	int PlayerState;                                 //0x4
	int StaminaTimer;                            //0x8
	unsigned short PlayerStance;            //0xC
	char _0x000E[0x2];                         //0xE
	int IsIngame;                                    //0x10
	char _0x0014[0x4];                         //0x14
	int iVelocity;                                   //0x18
	float Origin[3];                               //0x1C
	float Velocity[3];                            //0x28
	char _0x0034[0x2C];                      //0x34
	float RefViewAngleY;                    //0x60
	float RefViewAngleX;                    //0x64
	char _0x0068[0xE8];                      //0x68
	int ClientNumber;                          //0x150
	char _0x0154[0x4];                        //0x154
	float ViewAngleY;                         //0x158
	float ViewAngleX;                         //0x15C
	char _0x0160[0x3C];                     //0x160
	int Health;                                     //0x19C
	char _0x01A0[0x1C];                    //0x1A0
	int MaxEntities;                             //0x1BC
	char _0x01C0[0x44];                     //0x1C0
	int AdvancedUAV;                        //0x204
}CG_T; //0x8FF100

typedef struct
{
	char _0x0000[0x8];                         //0x0
	int Width;                                      //0x8
	int Height;                                     //0xC
	char _0x0010[0x14];                     //0x10
	char GameType[4];                       //0x24
	char _0x0028[0x1C];                    //0x28
	char HostName[64];                     //0x44
	char _0x0084[0xC4];                    //0x84
	int MaxClients;                             //0x148
	char _0x014C[0x4];                      //0x14C
	char MapName[64];                     //0x150
	char _0x0190[0x43F0];                //0x190
}CGS_T;

class CRadarHud
{
public:
	float x; //0x0000
	float y; //0x0004
	float w; //0x0008
	float h; //0x000C
	char _0x0010[12];
};


class CScreenMatrix
{
public:
	char _0x0000[64];
};


#endif // STRUCTS_H_INCLUDED
