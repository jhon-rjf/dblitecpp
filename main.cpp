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
