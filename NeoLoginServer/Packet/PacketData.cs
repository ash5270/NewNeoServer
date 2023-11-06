using System;
using System.Collections.Generic;
using neo.system;
namespace neo::packet::login {
public class P_C_REQ_CREATE_ID
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_CREATE_ID;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * id.Length) + sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int16) + (sizeof(Int16) * email.Length) + sizeof(Int16) + (sizeof(Int16) * password.Length) + sizeof(Int16) + (sizeof(Int16) * passwordCheck.Length) ;
		return size;
	}
	public string id;
	public string name;
	public string email;
	public string password;
	public string passwordCheck;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(id);
		buffer.Write(name);
		buffer.Write(email);
		buffer.Write(password);
		buffer.Write(passwordCheck);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out id);
		buffer.Read(out name);
		buffer.Read(out email);
		buffer.Read(out password);
		buffer.Read(out passwordCheck);

	}
};

public class P_C_REQ_CREATE_ID_CHECK
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_CREATE_ID_CHECK;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * id.Length) ;
		return size;
	}
	public string id;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(id);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out id);

	}
};

public class P_S_RES_CREATE_ID
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_CREATE_ID;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + sizeof(Int16) + (sizeof(Int16) * msg.Length) ;
		return size;
	}
	public Int32 statusCode;
	public string msg;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(statusCode);
		buffer.Write(msg);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out statusCode);
		buffer.Read(out msg);

	}
};

public class P_C_REQ_LOGIN
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_LOGIN;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * id.Length) + sizeof(Int16) + (sizeof(Int16) * password.Length) ;
		return size;
	}
	public string id;
	public string password;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(id);
		buffer.Write(password);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out id);
		buffer.Read(out password);

	}
};

public class P_S_RES_LOGIN
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_LOGIN;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + uuid.Length ;
		return size;
	}
	public Int32 statusCode;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(statusCode);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out statusCode);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class ChannelInfo
  {
	public Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public string name;
	public Int32 channelId;
	public Int32 userCount;
	

	public void Serialize(OutputMemoryStream buffer){
		buffer.Write(name);
		buffer.Write(channelId);
		buffer.Write(userCount);

	}
	public void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out name);
		buffer.Read(out channelId);
		buffer.Read(out userCount);

	}
};

public class CharSelectVeiwInfo
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

public class CharEnterInGameInfo
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

public class P_C_REQ_CHANNEL_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_CHANNEL_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += uuid.Length ;
		return size;
	}
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_RES_CHANNEL_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_CHANNEL_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<channelInfos.Count; i++){
			size+= channelInfos[i].GetSize();
		}
		
		return size;
	}
	public List<ChannelInfo> channelInfos = new List<ChannelInfo>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write((int)(channelInfos.Count));
		for(int i=0; i<channelInfos.Count; i++){
			channelInfos[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			ChannelInfo data = new ChannelInfo();
			data.Deserialize(buffer);
			channelInfos.Add(data);
		}

	}
};

public class P_C_REQ_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + uuid.Length ;
		return size;
	}
	public Int32 channelID;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(channelID);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out channelID);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_RES_CHAR_DATA
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_CHAR_DATA;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size+=sizeof(Int32);
		for(int i=0; i<charViewInfos.Count; i++){
			size+= charViewInfos[i].GetSize();
		}
		
		return size;
	}
	public List<CharSelectVeiwInfo> charViewInfos = new List<CharSelectVeiwInfo>();
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write((int)(charViewInfos.Count));
		for(int i=0; i<charViewInfos.Count; i++){
			charViewInfos[i].Serialize(buffer);
		}

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		size = 0;
		buffer.Read(out size);
		for(int i=0; i<size; i++){
			CharSelectVeiwInfo data = new CharSelectVeiwInfo();
			data.Deserialize(buffer);
			charViewInfos.Add(data);
		}

	}
};

public class P_C_REQ_CHAR_DATA_DEL
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_CHAR_DATA_DEL;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + uuid.Length ;
		return size;
	}
	public Int32 characterId;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(characterId);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out characterId);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_RES_CHAR_DATA_DEL
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_CHAR_DATA_DEL;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) ;
		return size;
	}
	public Int32 statusCode;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(statusCode);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out statusCode);

	}
};

public class P_C_REQ_CHAR_DATA_CRE
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_CHAR_DATA_CRE;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * name.Length) + sizeof(Int32) + sizeof(Int32) + sizeof(Int32) ;
		return size;
	}
	public string name;
	public Int32 channelId;
	public Int32 characterImageId;
	public Int32 characterWeaponId;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(name);
		buffer.Write(channelId);
		buffer.Write(characterImageId);
		buffer.Write(characterWeaponId);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out name);
		buffer.Read(out channelId);
		buffer.Read(out characterImageId);
		buffer.Read(out characterWeaponId);

	}
};

public class P_S_RES_CHAR_DATA_CRE
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_CHAR_DATA_CRE;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) ;
		return size;
	}
	public Int32 statusCode;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(statusCode);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out statusCode);

	}
};

public class P_C_REQ_GAME_SERVER_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_C_REQ_GAME_SERVER_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int32) + uuid.Length ;
		return size;
	}
	public Int32 channelId;
	public byte[] uuid =new byte[16];
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(channelId);
		buffer.Write(uuid, uuid.Length);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out channelId);
		buffer.Read(ref uuid, uuid.Length);

	}
};

public class P_S_RES_GAME_SERVER_INFO
 : Packet{
	public override PacketID GetID(){
		return PacketID.PI_S_RES_GAME_SERVER_INFO;
	}
	
public override Int32 GetSize(){
		Int32 size = 0;
		size += sizeof(Int16) + (sizeof(Int16) * ip.Length) + sizeof(Int32) ;
		return size;
	}
	public string ip;
	public Int32 port;
	

	public override void Serialize(OutputMemoryStream buffer){
		HeaderSerialize(buffer);
		buffer.Write(ip);
		buffer.Write(port);

	}

	public override void Deserialize(InputMemoryStream buffer){
		Int32 size=0;
		buffer.Read(out ip);
		buffer.Read(out port);

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
