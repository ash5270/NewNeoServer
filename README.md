# 기존에 진행했던 neoserver 프로젝트의 개선 버전을 개발중입니다.

마이크로 서비스 아키텍처를 사용하여 개발하고 있습니다. 

현재 서버는 아래와 같습니다.
1. 로그인 서버
2. 디비 서버
3. 게임 로직 서버

아직 개발은 못했지만 추가할 서버는 아래와 같습니다.
1. 채팅서버
2. 몬스터 로직 서버


## 로그인 서버는
로그인을 하게 되면 mysql에서 정보를 읽어와 로그인 성공이 redis에 유저 정보를 캐싱해둡니다.

