# 국립안동대학교 컴퓨터공학과 C++프로그래밍
#### 수업중 과제제출을 위해 만들어진 레포입니다. / cpp에서 sqlite를 사용하기 위해 배운 내용입니다.
db에는 3명의 학생 이름과 2개의 과목,각각의 점수가 들어있습니다.
cpp파일에서는 각각 학생들의 총점과 평균, 각각 과목별로 총점, 평균을 계산하게 만들었습니다.




---
##### 개발환경
  
  **OS :** MacOS Sonoma 14.4.1(23E224)

  **ChipSet :** Apple M1

  **통합개발환경 :** Xcode Version 15.3 (15E204a)

  **DATABASE :** sqlite 3.45.3

  


---
## MANUAL

 *1. sqlite를 다운받는다*
   
   ###### iterm zsh에서 실행
   ```bash
   brew install sqlite
   ```


  

 *2. database 생성*
 
  ```bash
  cd ~/Desktop/sqlitecpp
  sqlite3 sj.db
  ```


  

 *3. XCode 설정*

 
  a. 좌측 프로젝트 클릭 두번


  b. FILENAME.cpp.xcodeproj 이라는 프로젝트 파일이 열리면 **Build Phases** 열기 


  c. **Link Binary With Libraries**에 +버튼, libsqlite3.0tbd, libsqlite3.tbd 추가
  

  
 *4. cpp 파일 생성*
 
   a. 헤더파일 추가
   ```c++
   #include <sqlite3.h>
   ```

   b. 구조체만들기 
    수학점수의 총합과 영어 점수의 총합 저장, 처리된 학생 수를 저장한다.


   c. 콜백함수 선언
    불러온 db를 처리하는데에 사용한다.


   d. 학생들의 총합점수와 평균점수 출력
   ```c++
   cout << "학생 ID: " << argv[0] << ", 이름: " << argv[1] << endl;
   cout << "수학 점수: " << mathScore << ", 영어 점수: " << englishScore << endl;
   cout << "총점: " << sum << ", 평균: " << average << endl << endl;
   ```


   e. main
   
      1. db열기
      
      2. 쿼리실행
      
      3. db닫기
