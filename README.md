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

 **1. sqlite를 다운받는다**
   
   ###### iterm zsh에서 실행
   ```bash
   brew install sqlite
   ```
# 
<br/>
**2. database 생성 및 내용 추가**
 
  ```bash
  cd ~/Desktop/sqlitecpp
  sqlite3 sj.db
  ```
![grade table](https://github.com/jhon-rjf/dblitecpp/blob/main/grade_table%20.png)

#   
<br/>
**3. XCode 설정**

 
  a. 좌측 프로젝트 클릭 두번


  b. FILENAME.cpp.xcodeproj 이라는 프로젝트 파일이 열리면 **Build Phases** 열기 


  c. **Link Binary With Libraries**에 +버튼, libsqlite3.0tbd, libsqlite3.tbd 추가  

#  
<br/>
**4. cpp 파일 생성**
 
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


   ---
   ## CODE

   ### file PATH를 본 파일이 있는 절대경로로 맞춰준다. dbpath
   ```C++
    #include <iostream>
    #include <sqlite3.h>
    #include <string>
    
    using namespace std;
    
    // 학생별 점수와 과목별 점수를 추적하기 위한 구조체 정의
    struct Scores {
      int totalMath = 0;     // 수학 점수의 총합을 저장
      int totalEnglish = 0;  // 영어 점수의 총합을 저장
      int studentCount = 0;  // 처리된 학생 수를 계산
    };
    
    // 콜백 함수 선언
    static int callback(void* data, int argc, char** argv, char** azColName) {
      int mathScore = atoi(argv[2]); // 수학 점수를 정수로 변환
      int englishScore = atoi(argv[3]); // 영어 점수를 정수로 변환
      int sum = mathScore + englishScore; // 학생의 총점 계산
      double average = sum / 2.0; // 학생의 평균 점수 계산
    
      cout << "학생 ID: " << argv[0] << ", 이름: " << argv[1] << endl;
      cout << "수학 점수: " << mathScore << ", 영어 점수: " << englishScore << endl;
      cout << "총점: " << sum << ", 평균: " << average << endl << endl;
    
      // 과목별 총점 및 평균 계산을 위한 데이터 업데이트
      Scores* scores = static_cast<Scores*>(data);
      scores->totalMath += mathScore; // 수학 점수 누적
      scores->totalEnglish += englishScore; // 영어 점수 누적
      scores->studentCount++; // 학생 수 증가
    
      return 0;
    }
    
    int main() {
      sqlite3 *db; // SQLite 데이터베이스 객체 포인터 선언
      char *errmsg = 0; // 에러 메시지 포인터 초기화
    
      string dbPath = "/Users/jeong-yungeol/Downloads/databasecpp/sj.db"; // 데이터베이스 파일 경로
    
      // 데이터베이스 열기
      int rc = sqlite3_open(dbPath.c_str(), &db);
      if (rc) {
          cerr << "데이터베이스 열기 실패: " << sqlite3_errmsg(db) << endl;
          sqlite3_close(db); // 오류 시 데이터베이스 닫기
          return 1;
      } else {
          cout << "데이터베이스 성공적으로 열림." << endl;
      }
    
      // 쿼리 실행
      const char* sql = "SELECT id, name, math, english FROM grade;"; // SQL 쿼리 문자열
      Scores scores; // Scores 구조체 인스턴스 초기화
      rc = sqlite3_exec(db, sql, callback, &scores, &errmsg); // 쿼리 실행
      if (rc != SQLITE_OK) {
          cerr << "SQL error: " << errmsg << endl;
          sqlite3_free(errmsg); // 에러 메시지 메모리 해제
      } else {
          cout << "Records selected successfully." << endl;
          cout << "수학 총점: " << scores.totalMath << ", 평균: " << (double)scores.totalMath / scores.studentCount << endl;
          cout << "영어 총점: " << scores.totalEnglish << ", 평균: " << (double)scores.totalEnglish / scores.studentCount << endl;
      }
    
      // 데이터베이스 닫기
      sqlite3_close(db); // 데이터베이스 리소스 해제
      return 0;
    }
```

#
<br/>

# cpp result
![cpp_result](https://github.com/jhon-rjf/dblitecpp/blob/main/cppcapture.jpg)
