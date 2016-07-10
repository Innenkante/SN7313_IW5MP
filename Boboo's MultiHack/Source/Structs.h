#pragma once
#define PI 3.14159265358979323846264338327950288419716939937
struct Vector3D
{
	float x, y, z;
public:
	Vector3D(float xC, float yC, float zC)
	{
		x = xC;
		y = yC;
		z = zC;
	}
};

struct Vector2D
{
	float x;
	float y;
public:
	Vector2D(float xC, float yC)
	{
		x = xC;
		y = yC;
	}
};
typedef struct
{
	int ClientNumber; //0x0000 
	int Valid; //0x0004 
	char _0x0008[4];
	char Name[16]; //0x000C 
	int Team; //0x001C 
	int Team_2; //0x0020 
	int Rank; //0x0024 
	char _0x0028[16];
	int Perk; //0x0038 
	char _0x003C[8];
	int Score; //0x0044 
	char _0x0048[8];
	char BodyName[32]; //0x0050 
	char _0x0070[32];
	char HeadName[32]; //0x0090 
	char _0x00B0[992];
	BYTE IsStanding; //0x0490 
	BYTE IsWalking; //0x0491 
	BYTE IsSprinting; //0x0492 
	char _0x0493[13];
	int IsAttacking; //0x04A0 
	char _0x04A4[4];
	int IsZooming; //0x04A8 
	char _0x04AC[68];
	int WeaponNumber1; //0x04F0 
	char _0x04F4[24];
	int WeaponNumber2; //0x050C 
	char _0x0510[80];
}ClientInfo_T; 

typedef struct
{
	char _0x0000[0x8];
	int Width;
	int Height;
	int FovX;
	int FovY;
	Vector3D Origin;
	Vector3D ViewAxis[3];
	char _0x0048[0x24];
	float ZoomProgress;
	char _0x0070[0x4ABC];
	Vector3D ViewAngles;
	char _0x4B34[0x30];
	float WeaponViewAngleX;
	float WeaponViewAngleY;
}RefDef_T;

typedef struct
{
	float Recoil[3];                                   
	float Origin[3];                                   
	char _0x0018[0x80];                          
	float ViewAngleY;                             
	float ViewAngleX;                            
}viewmatrix_t;

enum Entity_Type
{
	General = 0,
	Player = 1,
	Player_Corpse = 2,
	Item = 3,
	Explosive = 4,
	Invisible = 5,
	ScriptMover = 6,
	Sound = 7,
	FX = 8,
	Loop_FX = 9,
	Primary_Light = 10,
	Turret = 11,
	Helicopter = 12,
	Plane = 13,
	Vehicle = 14,
	Vehicle_Map = 15,
	Vechicle_Corpse = 16,
	Vechicle_Spawner = 17
};



typedef struct
{
	char _0x0000[0x2];
	short Valid;
	char _0x0004[0x10];
	Vector3D Origin;
	Vector3D Angles;
	char _0x002C[0x3C];
	int Flags;
	char _0x006C[0xC];
	Vector3D OldOrigin;
	char _0x0084[0x18];
	Vector3D OldAngles;
	char _0x00A8[0x28];
	int ClientNumber;
	short Type;
	char _0x00D6[0x12];
	Vector3D NewOrigin;
	char _0x00F4[0x1C];
	Vector3D NewAngles;
	char _0x011C[0x7C];
	BYTE WeaponID;
	char _0x0199[0x37];
	int IsAlive;
	char _0x01D4[0x24];
}Entity_T;

typedef struct
{
	int ServerTime;                                 
	int PlayerState;                                 
	int StaminaTimer;                            
	unsigned short PlayerStance;            
	char _0x000E[0x2];                         
	int IsIngame;                                    
	char _0x0014[0x4];                         
	int iVelocity;                                   
	float Origin[3];                               
	float Velocity[3];                            
	char _0x0034[0x2C];                      
	float RefViewAngleY;                   
	float RefViewAngleX;                    
	char _0x0068[0xE8];                      
	int ClientNumber;                         
	char _0x0154[0x4];                        
	float ViewAngleY;                         
	float ViewAngleX;                         
	char _0x0160[0x3C];                     
	int Health;                                     
	char _0x01A0[0x1C];                    
	int MaxEntities;                             
	char _0x01C0[0x44];                     
	int AdvancedUAV;                        
}CG_T; 

typedef struct
{
	char _0x0000[0x8];                         
	int Width;                                      
	int Height;                                     
	char _0x0010[0x14];                     
	char GameType[4];                       
	char _0x0028[0x1C];                   
	char HostName[64];                     
	char _0x0084[0xC4];                    
	int MaxClients;                             
	char _0x014C[0x4];                      
	char MapName[64];                     
	char _0x0190[0x43F0];                
}CGS_T;

class RadarHud
{
public:
	float x; 
	float y; 
	float w; 
	float h; 
	char _0x0010[12];
};


class ScreenMatrix
{
public:
	char _0x0000[0xDC]; //64 before
};

class trace_t
{
public:
	float Fraction;
	char _0x0004[0x60];
};




