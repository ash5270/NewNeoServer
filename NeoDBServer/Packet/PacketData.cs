using System;
using System.Collections.Generic;
using neo.system;
namespace neo::packet::db {
public class P_S_REQ_DB_ENTER_INGAME_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_ENTER_INGAME_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 characterId;
	public Int32 channelId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(characterId);
		buffer.Write(channelId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out characterId);
		buffer.Read(out channelId);

	}
};

public class P_S_RES_DB_ENTER_INGAME_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_ENTER_INGAME_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * characterName.Length) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(float) + sizeof(float) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 mapId;
	public string characterName;
	public Int32 characterId;
	public Int32 characterImageId;
	public Int32 characterWeaponId;
	public float posX;
	public float posY;
	public Int32 animaionCode;
	public Int32 Level;
	public Int32 Hp;
	public Int32 MaxHP;
	

	public override void Serialize(OutputMemoryStream buffer){
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

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out mapId);
		buffer.Read(out characterName);
		buffer.Read(out characterId);
		buffer.Read(out characterImageId);
		buffer.Read(out characterWeaponId);
		buffer.Read(out posX);
		buffer.Read(out posY);
		buffer.Read(out animaionCode);
		buffer.Read(out Level);
		buffer.Read(out Hp);
		buffer.Read(out MaxHP);

	}
};

public class WorldMapData
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 id;
	public string name;
	public Int32 monsterCode;
	public Int32 monsterCount;
	

	public void Serialize(OutputMemoryStream buffer){
		buffer.Write(id);
		buffer.Write(name);
		buffer.Write(monsterCode);
		buffer.Write(monsterCount);

	}
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out id);
		buffer.Read(out name);
		buffer.Read(out monsterCode);
		buffer.Read(out monsterCount);

	}
};

public class P_S_REQ_DB_WORLD_MAP_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_WORLD_MAP_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);

	}
};

public class P_S_RES_DB_WORLD_MAP_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_WORLD_MAP_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<worldMapDatas.Count; i++){
			size+= worldMapDatas[i].GetSize();
		}
		
		return size;
	}
	public List<WorldMapData> worldMapDatas = new List<WorldMapData>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write((int)(worldMapDatas.Count));
		for(int i=0; i<worldMapDatas.Count; i++){
			worldMapDatas[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			WorldMapData data = new WorldMapData();
			data.Deserialize(buffer);
			worldMapDatas.Add(data);
		}

	}
};

public class P_S_REQ_DB_LOGIN
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_LOGIN;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(UInt64) + sizeof(Int16) + (sizeof(Int16) * id.Length) + sizeof(Int16) + (sizeof(Int16) * password.Length) + uuid.Length ;
		return size;
	}
	public UInt64 sessionId;
	public string id;
	public string password;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(id);
		buffer.Write(password);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out id);
		buffer.Read(out password);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_RES_DB_LOGIN
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_LOGIN;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(UInt64) + sizeof(bool) + uuid.Length ;
		return size;
	}
	public UInt64 sessionId;
	public bool isLogin;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(isLogin);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out isLogin);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class DBChannelData
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int16) + (sizeof(Int16) * channelId.Length) ;
		return size;
	}
	public string name;
	public string channelId;
	

	public void Serialize(OutputMemoryStream buffer){
		buffer.Write(name);
		buffer.Write(channelId);

	}
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out name);
		buffer.Read(out channelId);

	}
};

public class DBCharSelectVeiwData
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public string name;
	public Int32 id;
	public Int32 characterImageId;
	public Int32 characterWeaponId;
	public Int32 characterLevel;
	

	public void Serialize(OutputMemoryStream buffer){
		buffer.Write(name);
		buffer.Write(id);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);
		buffer.Write(characterLevel);

	}
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out name);
		buffer.Read(out id);
		buffer.Read(out characterImageId);
		buffer.Read(out characterWeaponId);
		buffer.Read(out characterLevel);

	}
};

public class DBCharInGameEnterData
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) + sizeof(float) + sizeof(float) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public string name;
	public Int32 characterId;
	public Int32 characterImageId;
	public Int32 characterWeaponId;
	public Int32 characterLevel;
	public float posX;
	public float posY;
	public Int32 characterExp;
	public Int32 characterHp;
	public Int32 characterMaxHp;
	

	public void Serialize(OutputMemoryStream buffer){
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
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out name);
		buffer.Read(out characterId);
		buffer.Read(out characterImageId);
		buffer.Read(out characterWeaponId);
		buffer.Read(out characterLevel);
		buffer.Read(out posX);
		buffer.Read(out posY);
		buffer.Read(out characterExp);
		buffer.Read(out characterHp);
		buffer.Read(out characterMaxHp);

	}
};

public class P_S_REQ_DB_CHANNEL_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_CHANNEL_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(UInt64) ;
		return size;
	}
	public UInt64 sessionId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);

	}
};

public class P_S_RES_DB_CHANNEL_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_CHANNEL_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<channelInfos.Count; i++){
			size+= channelInfos[i].GetSize();
		}
		size += sizeof(UInt64) ;
		return size;
	}
	public UInt64 sessionId;
	public List<DBChannelData> channelInfos = new List<DBChannelData>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write((int)(channelInfos.Count));
		for(int i=0; i<channelInfos.Count; i++){
			channelInfos[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			DBChannelData data = new DBChannelData();
			data.Deserialize(buffer);
			channelInfos.Add(data);
		}

	}
};

public class P_S_REQ_DB_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * userId.Length) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 channelId;
	public string userId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(channelId);
		buffer.Write(userId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out channelId);
		buffer.Read(out userId);

	}
};

public class P_S_RES_DB_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<charViewDatas.Count; i++){
			size+= charViewDatas[i].GetSize();
		}
		size += sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public List<DBCharSelectVeiwData> charViewDatas = new List<DBCharSelectVeiwData>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write((int)(charViewDatas.Count));
		for(int i=0; i<charViewDatas.Count; i++){
			charViewDatas[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			DBCharSelectVeiwData data = new DBCharSelectVeiwData();
			data.Deserialize(buffer);
			charViewDatas.Add(data);
		}

	}
};

public class P_S_REQ_DB_CHAR_DATA_DEL
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_CHAR_DATA_DEL;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 characterid;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(characterid);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out characterid);

	}
};

public class P_S_RES_DB_CHAR_DATA_DEL
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_CHAR_DATA_DEL;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 statusCode;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(statusCode);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out statusCode);

	}
};

public class P_S_REQ_DB_CHAR_DATA_CRE
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_CHAR_DATA_CRE;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public string name;
	public Int32 channelId;
	public Int32 characterImageId;
	public Int32 characterWeaponId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(name);
		buffer.Write(channelId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out name);
		buffer.Read(out channelId);
		buffer.Read(out characterImageId);
		buffer.Read(out characterWeaponId);

	}
};

public class P_S_RES_DB_CHAR_DATA_CRE
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_CHAR_DATA_CRE;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 statusCode;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(statusCode);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out statusCode);

	}
};

public class P_S_REQ_DB_ID_CHECK
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_ID_CHECK;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * id.Length) ;
		return size;
	}
	public Int32 sessionId;
	public string id;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(id);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out id);

	}
};

public class P_S_REQ_DB_ID_CREATE
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_REQ_DB_ID_CREATE;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * id.Length) + sizeof(Int16) + (sizeof(Int16) * password.Length) + sizeof(Int16) + (sizeof(Int16) * email.Length) + sizeof(Int16) + (sizeof(Int16) * name.Length) ;
		return size;
	}
	public Int32 sessionId;
	public string id;
	public string password;
	public string email;
	public string name;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(id);
		buffer.Write(password);
		buffer.Write(email);
		buffer.Write(name);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out id);
		buffer.Read(out password);
		buffer.Read(out email);
		buffer.Read(out name);

	}
};

public class P_S_RES_DB_ID_CREATE
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_DB_ID_CREATE;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * msg.Length) ;
		return size;
	}
	public Int32 sessionId;
	public Int32 statusCode;
	public string msg;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(sessionId);
		buffer.Write(statusCode);
		buffer.Write(msg);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out sessionId);
		buffer.Read(out statusCode);
		buffer.Read(out msg);

	}
};

}
