#pragma once
#include"PacketID.h"
#include"Packet.h"

namespace neo::packet::login {
class P_S_REQ_DB_LOGIN
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_REQ_DB_LOGIN;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(uint64_t) + sizeof(int16_t) + (sizeof(wchar_t) * id.length()) + sizeof(int16_t) + (sizeof(wchar_t) * password.length()) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	uint64_t sessionId;
	std::wstring id;
	std::wstring password;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(id);
		buffer.Write(password);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(id);
		buffer.Read(password);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class P_S_RES_DB_LOGIN
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_DB_LOGIN;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(uint64_t) + sizeof(bool) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	uint64_t sessionId;
	bool isLogin;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(isLogin);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(isLogin);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class DBChannelData
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int16_t) + (sizeof(wchar_t) * channelId.length()) ;
		return static_cast<int32_t>(size);
	}
	std::wstring name;
	std::wstring channelId;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(name);
		buffer.Write(channelId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(name);
		buffer.Read(channelId);

	}
};

class DBCharSelectVeiwData
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	std::wstring name;
	int32_t id;
	int32_t characterImageId;
	int32_t characterWeaponId;
	int32_t characterLevel;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(name);
		buffer.Write(id);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(characterLevel);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(name);
		buffer.Read(id);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);
		buffer.Read(characterLevel);

	}
};

class DBCharInGameEnterData
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(float) + sizeof(float) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	std::wstring name;
	int32_t characterId;
	int32_t characterImageId;
	int32_t characterWeaponId;
	int32_t characterLevel;
	float posX;
	float posY;
	int32_t characterExp;
	int32_t characterHp;
	int32_t characterMaxHp;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(name);
		buffer.Write(characterId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(characterLevel);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(characterExp);
		buffer.Write(characterHp);
		buffer.Write(characterMaxHp);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(name);
		buffer.Read(characterId);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);
		buffer.Read(characterLevel);
		buffer.Read(posX);
		buffer.Read(posY);
		buffer.Read(characterExp);
		buffer.Read(characterHp);
		buffer.Read(characterMaxHp);

	}
};

class P_S_REQ_DB_CHANNEL_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_REQ_DB_CHANNEL_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(uint64_t) ;
		return static_cast<int32_t>(size);
	}
	
	uint64_t sessionId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);

	}
};

class P_S_RES_DB_CHANNEL_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_DB_CHANNEL_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<channelInfos.size(); i++){
			size+= channelInfos[i].GetSize();
		}
		size += sizeof(uint64_t) ;
		return static_cast<int32_t>(size);
	}
	
	uint64_t sessionId;
	std::vector<DBChannelData> channelInfos;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(static_cast<int32_t>(channelInfos.size()));
		for(int i=0; i<channelInfos.size(); i++){
			channelInfos[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			DBChannelData data;
			data.Deserialize(buffer);
			channelInfos.push_back(data);
		}

	}
};

class P_S_REQ_DB_CHAR_DATA
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_REQ_DB_CHAR_DATA;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * userId.length()) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	int32_t channelId;
	std::wstring userId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(channelId);
		buffer.Write(userId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(channelId);
		buffer.Read(userId);

	}
};

class P_S_RES_DB_CHAR_DATA
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_DB_CHAR_DATA;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<charViewDatas.size(); i++){
			size+= charViewDatas[i].GetSize();
		}
		size += sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	std::vector<DBCharSelectVeiwData> charViewDatas;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(static_cast<int32_t>(charViewDatas.size()));
		for(int i=0; i<charViewDatas.size(); i++){
			charViewDatas[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			DBCharSelectVeiwData data;
			data.Deserialize(buffer);
			charViewDatas.push_back(data);
		}

	}
};

class P_S_REQ_DB_CHAR_DATA_DEL
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_REQ_DB_CHAR_DATA_DEL;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	int32_t characterid;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(characterid);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(characterid);

	}
};

class P_S_RES_DB_CHAR_DATA_DEL
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_DB_CHAR_DATA_DEL;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	int32_t statusCode;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(statusCode);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(statusCode);

	}
};

class P_S_REQ_DB_CHAR_DATA_CRE
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_REQ_DB_CHAR_DATA_CRE;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	std::wstring name;
	int32_t channelId;
	int32_t characterImageId;
	int32_t characterWeaponId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(name);
		buffer.Write(channelId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(name);
		buffer.Read(channelId);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);

	}
};

class P_S_RES_DB_CHAR_DATA_CRE
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_DB_CHAR_DATA_CRE;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t sessionId;
	int32_t statusCode;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(statusCode);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(sessionId);
		buffer.Read(statusCode);

	}
};

class P_C_REQ_LOGIN
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_LOGIN;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * id.length()) + sizeof(int16_t) + (sizeof(wchar_t) * password.length()) ;
		return static_cast<int32_t>(size);
	}
	
	std::wstring id;
	std::wstring password;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(id);
		buffer.Write(password);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(id);
		buffer.Read(password);

	}
};

class P_S_RES_LOGIN
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_LOGIN;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t statusCode;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(statusCode);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(statusCode);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class ChannelInfo
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	std::wstring name;
	int32_t channelId;
	int32_t userCount;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(name);
		buffer.Write(channelId);
		buffer.Write(userCount);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(name);
		buffer.Read(channelId);
		buffer.Read(userCount);

	}
};

class CharSelectVeiwInfo
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	std::wstring name;
	int32_t id;
	int32_t characterImageId;
	int32_t characterWeaponId;
	int32_t characterLevel;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(name);
		buffer.Write(id);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(characterLevel);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(name);
		buffer.Read(id);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);
		buffer.Read(characterLevel);

	}
};

class CharEnterInGameInfo
 {
public:
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) + sizeof(float) + sizeof(float) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	std::wstring name;
	int32_t characterId;
	int32_t characterImageId;
	int32_t characterWeaponId;
	int32_t characterLevel;
	float posX;
	float posY;
	int32_t characterExp;
	int32_t characterHp;
	int32_t characterMaxHp;
	

	void Serialize(OutputMemoryStream& buffer){
		buffer.Write(name);
		buffer.Write(characterId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(characterLevel);
		buffer.Write(posX);
		buffer.Write(posY);
		buffer.Write(characterExp);
		buffer.Write(characterHp);
		buffer.Write(characterMaxHp);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(name);
		buffer.Read(characterId);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);
		buffer.Read(characterLevel);
		buffer.Read(posX);
		buffer.Read(posY);
		buffer.Read(characterExp);
		buffer.Read(characterHp);
		buffer.Read(characterMaxHp);

	}
};

class P_C_REQ_CHANNEL_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_CHANNEL_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(uuid,sizeof(uuid));

	}
};

class P_S_RES_CHANNEL_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_CHANNEL_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<channelInfos.size(); i++){
			size+= channelInfos[i].GetSize();
		}
		
		return static_cast<int32_t>(size);
	}
	
	std::vector<ChannelInfo> channelInfos;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(static_cast<int32_t>(channelInfos.size()));
		for(int i=0; i<channelInfos.size(); i++){
			channelInfos[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			ChannelInfo data;
			data.Deserialize(buffer);
			channelInfos.push_back(data);
		}

	}
};

class P_C_REQ_CHAR_DATA
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_CHAR_DATA;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t channelID;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(channelID);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(channelID);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class P_S_RES_CHAR_DATA
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_CHAR_DATA;
	}
	int32_t GetSize(){
		size_t size =0;
		size+=sizeof(int32_t);
		for(int i=0; i<charViewInfos.size(); i++){
			size+= charViewInfos[i].GetSize();
		}
		
		return static_cast<int32_t>(size);
	}
	
	std::vector<CharSelectVeiwInfo> charViewInfos;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(static_cast<int32_t>(charViewInfos.size()));
		for(int i=0; i<charViewInfos.size(); i++){
			charViewInfos[i].Serialize(buffer);
		}

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		size = 0;
		buffer.Read(size);
		for(int i=0; i<size; i++){
			CharSelectVeiwInfo data;
			data.Deserialize(buffer);
			charViewInfos.push_back(data);
		}

	}
};

class P_C_REQ_CHAR_DATA_DEL
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_CHAR_DATA_DEL;
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

class P_S_RES_CHAR_DATA_DEL
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_CHAR_DATA_DEL;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t statusCode;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(statusCode);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(statusCode);

	}
};

class P_C_REQ_CHAR_DATA_CRE
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_CHAR_DATA_CRE;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * name.length()) + sizeof(int32_t) + sizeof(int32_t) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	std::wstring name;
	int32_t channelId;
	int32_t characterImageId;
	int32_t characterWeaponId;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(name);
		buffer.Write(channelId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(name);
		buffer.Read(channelId);
		buffer.Read(characterImageId);
		buffer.Read(characterWeaponId);

	}
};

class P_S_RES_CHAR_DATA_CRE
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_CHAR_DATA_CRE;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t statusCode;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(statusCode);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(statusCode);

	}
};

class P_C_REQ_GAME_SERVER_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_C_REQ_GAME_SERVER_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int32_t) + sizeof(uuid) ;
		return static_cast<int32_t>(size);
	}
	
	int32_t channelId;
	uint8_t uuid[16];
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(channelId);
		buffer.Write(uuid,sizeof(uuid));

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(channelId);
		buffer.Read(uuid,sizeof(uuid));

	}
};

class P_S_RES_GAME_SERVER_INFO
 : public Packet{
public:
	PacketID GetID(){
		 return PacketID::PI_S_RES_GAME_SERVER_INFO;
	}
	int32_t GetSize(){
		size_t size =0;
		size += sizeof(int16_t) + (sizeof(wchar_t) * ip.length()) + sizeof(int32_t) ;
		return static_cast<int32_t>(size);
	}
	
	std::wstring ip;
	int32_t port;
	

	void Serialize(OutputMemoryStream& buffer){
	HeaderSerialize(buffer);
		buffer.Write(ip);
		buffer.Write(port);

	}

	void Deserialize(InputMemoryStream& buffer){
		int32_t size=0;
		buffer.Read(ip);
		buffer.Read(port);

	}
};

}
