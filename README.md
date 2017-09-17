# debug_log_monitor

[원본블로그](http://blog.naver.com/adsloader/50141481480)

### 목적
 
- window에서 서버를 개발하다보면 디버깅을 하기 위해 log를 많이 사용하는 경우가 많다. 
- 통신에 프로그램에 log를 사용하다보면 속도저하와 시스템 불안  있다. 

서버 프로그램의 경우, 디버깅을 할 수 있는 경우가 적기 때문에 log에 많은 의존을 한다.
그러다보니 “log를 추가/삭제”하는 일이 빈번하게 되고 그로인한 예기치않은 버그도 생기게 된다.
 
그러므로 서버 개발(또는 디버깅)을 할 때는 디버깅 메시지가 출력되고 실제 서비스 될 때는 
디버깅 메시지가 출력 안되게 할 필요가 생긴다.
 
이런 목적을 달성하기 위해 windows의 OutputDebugString() 함수와 Debugging API를 사용해보도록 한다.

### 구성
 
![](http://postfiles1.naver.net/20120518_128/adsloader_1337345035247fu8fT_JPEG/1.PNG?type=w2)


## 실행

![](/data/debugmonitor.gif)

