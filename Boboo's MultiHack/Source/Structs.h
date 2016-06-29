#pragma once
#define PI 3.14159265358979323846264338327950288419716939937
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
	static Vector Subtract(Vector vec1, Vector vec2)
	{
		Vector v(0, 0, 0);
		v.x = vec1.x - vec2.x;
		v.y = vec1.y - vec2.y;
		v.z = vec1.z - vec2.z;

		return v;
	}

	float Length()
	{
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}

	static void CalcVecToAngle(Vector vec,float** outAngles)
	{
		*outAngles[0] = atan2(vec.x, vec.y) * PI / 180.0f;
		*outAngles[1] = atan2(vec.z, vec.y) * PI / 180.0f;
	}


};

typedef struct
{
	int Valid;                     
	char _0x0004[0x8];             
	char Name[16];                 
	int Team;                      
	char _0x0020[0x4];             
	int Rank;                      
	char _0x0028[0x10];            
	int Perk;                      
	char _0x003C[0x8];            
	int Score;                     
	char _0x0048[0x458];           
	int Attacking;                 
	char _0x04A4[0x4];             
	int Zooming;                         
	char _0x04AC[0xB8];            
}ClientInfo_T; 

typedef struct
{
	char _0x0000[0x8];                       
	int Width;                                     
	int Height;                                   
	int FovX;                                      
	int FovY;                                      
	Vector Origin;                             
	Vector ViewAngles;                
	char _0x0048[0x24];                    
	float ZoomProgress;                     
	char _0x0070[0x4ABC];              
	float RefViewAngleY;                 
	float RefViewAngleX;                 
	char _0x4B34[0x34];                   
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

typedef struct
{
	char _0x0000[0x2];
	short Valid;
	char _0x0004[0x10];
	Vector Origin;
	Vector Angles;
	char _0x002C[0x3C];
	int Flags;
	char _0x006C[0xC];
	Vector OldOrigin;
	char _0x0084[0x18];
	Vector OldAngles;
	char _0x00A8[0x28];
	int ClientNumber;
	short Type;
	char _0x00D6[0x12];
	Vector NewOrigin;
	char _0x00F4[0x1C];
	Vector NewAngles;
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
	char _0x0000[64];
};


