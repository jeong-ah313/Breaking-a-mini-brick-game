# Breaking-a-mini-brick-game
* 완성본(기능구현이 더 추가됨)

https://user-images.githubusercontent.com/72932028/142924453-ffb3075d-efc3-4fe1-8d38-1bef62160003.mp4

* 미완성본(기능구현이 덜 되어 있음)

https://user-images.githubusercontent.com/72932028/142931770-c6f1bffa-db6b-4005-8131-0112423758e4.mp4


* 1. 프로그램명

미니 벽돌깨기 게임의 완성

* 2. 프로그램 설명

  화면에 “PRESS ANY KEY!”라는 문자가 적혀있고, 이는 키보드의 아무 키나 누르면 사라지면서 벽돌을 깨는 게임이 시작된다. 벽돌게임은 바를 조정하여 볼로 6개의 블록과 모두 충돌하면 “GAME OVER!”이라는 문자가 출력되면서 게임이 종료된다.

   * 변수 설명     : 
   * 
   우선 #define으로 BALL_SIZE(볼의 크기 상수), BAR_HOR_SIZE(바의 수평 크기 상수), BAR_VER_SIZE(바의 수직 크기 상수), BLOCK_HOR_SIZE(블록의 수평 크기 상수), BLOCK_VER_SIZE(블록의 수직 크기 상수), MOVE_STEP(볼의 이동 간격 상수)와 소리를 내기 위한 음계를 정의해주었다.
  
  메인함수에서는 bar_x와 bar_y(바의 x, y 좌표), ball_x와 ball_y(공의 x, y 좌표), block_x와 block_y(블록의 x,y좌표), dx와 dy(x, y의 좌표 이동값), i(블록을 그려주기 위해 필요한 변수), meet(6개의 블록 중에 충돌한 블록의 개수)와 meet0~6(충돌한 블록을 구별해 주기 위해 필요한 변수)들의 값들을 설정해주었다.

   * 알고리즘 설명 : 
   * 
   ① “PRESS ANY KEY!”가 출력된 화면이 보이면, 키보드의 아무 키나 누른다.
   ② 공이 내려오면서 벽돌을 깨는 게임이 시작된다.
   ③ 공은 막대에 부딪히면 팅겨져 나가며, 파랑색 박스의 위쪽과 좌우에 부딪히거나 벽돌에 부딪힌 경우에도 팅겨져 나간다. 만약 바로 공을 받지 못했다면, 공의 위치는 초기화되어 다시 떨어진다. 또한, 이때마다 소리가 발생한다.
   ④ 공으로 벽돌을 깰 수 있도록 바를 잘 조정한다.
   ⑤ 공과 벽돌이 충돌하면 meet와 meet0~5가 하나씩 증가한다. 벽돌은 사라지고, 오른쪽 상단의 score에 100점씩 점수가 올라간다. 
   ⑥ 공과 벽돌이 이미 충동하여 없어진 위치에 공이 또 충돌하면, if문으로 meet가 0보다 크다고 설정하여 벽돌과 공이 충돌한 위치를 지나쳐 간다.
   ⑦ 6개의 벽돌과 모두 충돌하여 벽돌이 없어지면, 화면에 “GAME OVER!”가 출력된다. score의 총점은 600점이다.

* 3. 소스코드 

   * 소스코드 설명 : 
   
  처음에 변수를 설명하는 부분은 2번 프로그램 설명에서 변수 설명 부분을 참고해주세요.
  테두리는 파랑색이고 배경은 흰색인 박스를 만들고, 상자 아래에는 "BAR X control : j, J, k, K" 문자열을 나타내어줍니다. 또한, 파랑색 박스 바깥 오른쪽 상단에는 점수를 출력하는 문자열 코드를 작성해줍니다.
  
  다음으로는 for문을 사용하여, 6개의 박스를 일정한 간격으로 만들어서 배치해주었습니다. 박스의 체두리는 검정색, 채우는 색은 갈색으로 설정하여 주었습니다.
  while문에서 !kbhit()와 _getch함수를 사용하여, “PRESS ANY KEY” 문구를 화면의 중간에 출력하여 보여주게 합니다. 이때 키보드를 눌렀는지 확인하기 위하여 _getch함수가 사용되었습니다. 키보드의 아무 키나 눌러주게 되면 게임이 실행되는데, 화면에 출력했던 “PRESS ANY KEY” 문구를 지워주기 위해 흰색 배경과 테두리는 가진 직사각형을 이용하여 문구를 지워줍니다.
  
  while(1)의 무한루프를 이용하여 게임을 실행시켜줍니다. 테두리는 파랑색이고 채우는 색은 빨강색인 공(ball)과 막대(bar)를 그려줍니다. 시간지연 함수 sleep을 사용하여 계속 나타날 수 있도록 해주고, 테두리와 채우는 색이 모두 흰색인 원을 그려서 공(ball)과 막대(bar)를 움직일때마다 지워줍니다. if문에서 _getch함수를 사용하여 막대(bar)가 j,k,J,K를 사용하여 오른쪽 왼쪽으로 움직일 수 있도록 해줍니다. 이때 논리연산자를 사용하여 소문자 j, k 뿐만 아니라 대문자 J, K를 사용해서도 막대(bar)를 움직이게 해줍니다. 그리고 if문에서 논리 연산자를 사용하여 공과 막대가 만나면 공이 팅겨져 나가도록 공의 dy의 이동값을 설정해주고 소리함수를 발생시켜줍니다. 그리고 공은 막대뿐만 아니라, 파랑색박스 테두리의 오른쪽과 왼쪽, 위쪽과 부딪혔을때에도 팅겨져 나가며 소리함수를 발생하도록 코드를 작성하여주었습니다. 그리고 첫 번째 블록(가장 왼쪽 블록)과 공이 만나서 부딪혔을 경우에는 팅겨져 나가면서 소리함수를 발생시켰으며, 이때 meet0(첫번째블록과 ball이 만난 것을 저장해주기 위한 변수)와 meet(6개의 블록과 ball이 모두 충돌했는지 알아보기 위한 변수)를 ++하여 1씩 증가시켜줍니다. 이와 같은 방식으로 6개의 블록과 공과의 관계를 설정하여줍니다. 그리고 각 블록들과 ball이 만난 경우에는 if(meet0>0)을 사용하여 그 위치에서 충돌하지 않고 그냥 지나가게 하는 코드들을 작성해주었습니다. 그리고 블록의 위치에 ball이 닿는경우에도 흰색 직사각형으로 블록을 지워주는 코드를 작성하였습니다. 또한, if문에서 meet변수를 사용하여 meet변수에 따라 score가 100씩 증가하여 보이도록 코드를 작성하였으며, 마지막 블록과 충돌할 때(=> meet=6)는 “GAME OVER!” 문자열을 화면 중앙에 표시하여 게임이 종료된 것을 나타내줍니다. 


