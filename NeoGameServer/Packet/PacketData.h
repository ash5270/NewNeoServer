#pragma once
#include"PacketID.h"
#include"Packet.h"

namespace neo::packet::game {
class P_C_NOTIFY_PING
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_NOTIFY_PING;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int64_t) ;
		return static_cast<int32_t>(size);
	}
	
	int64_t time;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(time);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(time);

	}
};

class P_C_NOTIFY_RTT
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_NOTIFY_RTT;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int64_t) ;
		return static_cast<int32_t>(size);
	}
	
	int64_t time;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(time);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(time);

	}
};

class P_S_NOTIFY_PING
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_NOTIFY_PING;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int64_t) ;
		return static_cast<int32_t>(size);
	}
	
	int64_t time;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(time);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(time);

	}
};

class P_S_NOTIFY_RTT
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_NOTIFY_RTT;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int64_t) ;
		return static_cast<int32_t>(size);
	}
	
	int64_t time;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(time);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(time);

	}
};

class PlayerData
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	int32_t characterId;
	int32_t mapId;
	std::wstring name;
	int32_t characterImageId;
	int32_t characterWeaponId;
	float posX;
	float posY;
	float velocityX;
	float velocityY;
	int32_t animaionCode;
	int32_t Level;
	int32_t Hp;
	int32_t MaxHP;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(characterId);
		buffer.Write(mapId);
		buffer.Write(name);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(velocityX);
		buffer.Write(velocityY);
		buffer.Write(animaionCode);
		buffer.Write(Level);
		buffer.Write(Hp);
		buffer.Write(MaxHP);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(characterId);
		buffer.Read(mapId);
		buffer.Read(name);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);
		buffer.Read(posX);
		buffer.Read(posY);
		buffer.Read(velocityX);
		buffer.Read(velocityY);
		buffer.Read(animaionCode);
		buffer.Read(Level);
		buffer.Read(Hp);
		buffer.Read(MaxHP);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class PlayerPosData
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	int32_t characterId;
	int32_t mapId;
	float posX;
	float posY;
	float velocityX;
	float velocityY;
	int32_t animaionCode;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(characterId);
		buffer.Write(mapId);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(velocityX);
		buffer.Write(velocityY);
		buffer.Write(animaionCode);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(characterId);
		buffer.Read(mapId);
		buffer.Read(posX);
		buffer.Read(posY);
		buffer.Read(velocityX);
		buffer.Read(velocityY);
		buffer.Read(animaionCode);

	}
};

class P_C_UPDATE_CHAR_POSITION
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_UPDATE_CHAR_POSITION;
	}
	int32_t GetSize(){
		size_t size =0;
		size += playerPosition.GetSize() + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	PlayerPosData playerPosition;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		playerPosition.Serialize(buffer);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		playerPosition.Deserialize(buffer);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class P_S_NOTIFY_CHAR_POSITION
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_NOTIFY_CHAR_POSITION;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<playerPosition.size(); i++){
			size+= playerPosition[i].GetSize();
		}
		
		return static_cast<int32_t>(size);
	}
	
	std::vector<PlayerPosData> playerPosition;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(static_cast<int32_t>(playerPosition.size()));
		for(int i=0; i<playerPosition.size(); i++){
			playerPosition[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			PlayerPosData data;
			data.Deserialize(buffer);
			playerPosition.push_back(data);
		}

	}
};

class P_C_REQ_WORLD_ENTER_THE_SERVER
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_WORLD_ENTER_THE_SERVER;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t characterId;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(characterId);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(characterId);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class P_S_RES_WORLD_PLAYER_DATA
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_WORLD_PLAYER_DATA;
	}
	int32_t GetSize(){
		size_t size =0;
		size += playerData.GetSize() ;
		return static_cast<int32_t>(size);
	}
	
	PlayerData playerData;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		playerData.Serialize(buffer);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		playerData.Deserialize(buffer);

	}
};

class P_S_RES_WORLD_CHARACTERS
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_WORLD_CHARACTERS;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<playerDatas.size(); i++){
			size+= playerDatas[i].GetSize();
		}
		
		return static_cast<int32_t>(size);
	}
	
	std::vector<PlayerData> playerDatas;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(static_cast<int32_t>(playerDatas.size()));
		for(int i=0; i<playerDatas.size(); i++){
			playerDatas[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			PlayerData data;
			data.Deserialize(buffer);
			playerDatas.push_back(data);
		}

	}
};

class P_S_RES_WORLD_MONSTERS
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_WORLD_MONSTERS;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<playerDatas.size(); i++){
			size+= playerDatas[i].GetSize();
		}
		
		return static_cast<int32_t>(size);
	}
	
	std::vector<PlayerData> playerDatas;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(static_cast<int32_t>(playerDatas.size()));
		for(int i=0; i<playerDatas.size(); i++){
			playerDatas[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			PlayerData data;
			data.Deserialize(buffer);
			playerDatas.push_back(data);
		}

	}
};

class P_S_CLOSE_WORLD
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_CLOSE_WORLD;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t characterId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(characterId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(characterId);

	}
};

class P_S_NOTIFY_LEAVE_WORLD_PLAYER
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_NOTIFY_LEAVE_WORLD_PLAYER;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t characterId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(characterId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(characterId);

	}
};

class P_C_REQ_LEAVE_MAP
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_LEAVE_MAP;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t leaveMapId;
	int32_t enterMapId;
	int32_t characterId;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(leaveMapId);
		buffer.Write(enterMapId);
		buffer.Write(characterId);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(leaveMapId);
		buffer.Read(enterMapId);
		buffer.Read(characterId);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class P_S_RES_ENTER_MAP
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_ENTER_MAP;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(float) + sizeof(float) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	float posX;
	float posY;
	int32_t enterMapId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(enterMapId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(posX);
		buffer.Read(posY);
		buffer.Read(enterMapId);

	}
};

class P_S_REQ_DB_ENTER_INGAME_CHAR_DATA
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_REQ_DB_ENTER_INGAME_CHAR_DATA;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	int32_t characterId;
	int32_t channelId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(characterId);
		buffer.Write(channelId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(characterId);
		buffer.Read(channelId);

	}
};

class P_S_RES_DB_ENTER_INGAME_CHAR_DATA
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_DB_ENTER_INGAME_CHAR_DATA;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * characterName.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(float) + sizeof(float) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	int32_t mapId;
	std::wstring characterName;
	int32_t characterId;
	int32_t characterImageId;
	int32_t characterWeaponId;
	float posX;
	float posY;
	int32_t animaionCode;
	int32_t Level;
	int32_t Hp;
	int32_t MaxHP;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(mapId);
		buffer.Write(characterName);
		buffer.Write(characterId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(animaionCode);
		buffer.Write(Level);
		buffer.Write(Hp);
		buffer.Write(MaxHP);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(mapId);
		buffer.Read(characterName);
		buffer.Read(characterId);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);
		buffer.Read(posX);
		buffer.Read(posY);
		buffer.Read(animaionCode);
		buffer.Read(Level);
		buffer.Read(Hp);
		buffer.Read(MaxHP);

	}
};

class WorldMapData
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	int32_t id;
	std::wstring name;
	int32_t monsterCode;
	int32_t monsterCount;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(id);
		buffer.Write(name);
		buffer.Write(monsterCode);
		buffer.Write(monsterCount);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(id);
		buffer.Read(name);
		buffer.Read(monsterCode);
		buffer.Read(monsterCount);

	}
};

class P_S_REQ_DB_WORLD_MAP_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_REQ_DB_WORLD_MAP_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);

	}
};

class P_S_RES_DB_WORLD_MAP_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_DB_WORLD_MAP_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<worldMapDatas.size(); i++){
			size+= worldMapDatas[i].GetSize();
		}
		
		return static_cast<int32_t>(size);
	}
	
	std::vector<WorldMapData> worldMapDatas;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(static_cast<int32_t>(worldMapDatas.size()));
		for(int i=0; i<worldMapDatas.size(); i++){
			worldMapDatas[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			WorldMapData data;
			data.Deserialize(buffer);
			worldMapDatas.push_back(data);
		}

	}
};

}
