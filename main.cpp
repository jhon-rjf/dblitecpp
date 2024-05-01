#include <iostream>
#include <sqlite3.h>
#include <string>

using namespace std;

// 학생별 점수와 과목별 점수를 추적하기 위한 구조체 정의
struct Scores {
    int totalMath = 0;
    int totalEnglish = 0;
    int studentCount = 0;
};

// 콜백 함수 선언
static int callback(void* data, int argc, char** argv, char** azColName) {
    int mathScore = atoi(argv[2]);
    int englishScore = atoi(argv[3]);
    int sum = mathScore + englishScore;
    double average = sum / 2.0;

    cout << "학생 ID: " << argv[0] << ", 이름: " << argv[1] << endl;
    cout << "수학 점수: " << mathScore << ", 영어 점수: " << englishScore << endl;
    cout << "총점: " << sum << ", 평균: " << average << endl << endl;

    // 과목별 총점 및 평균 계산을 위한 데이터 업데이트
    Scores* scores = static_cast<Scores*>(data);
    scores->totalMath += mathScore;
    scores->totalEnglish += englishScore;
    scores->studentCount++;

    return 0;
}

int main() {
    sqlite3 *db;
    char *errmsg = 0;

    string dbPath = "/Users/jeong-yungeol/Downloads/databasecpp/sj.db";

    // 데이터베이스 열기
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) {
        cerr << "데이터베이스 열기 실패: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return 1;
    } else {
        cout << "데이터베이스 성공적으로 열림." << endl;
    }

    // 쿼리 실행
    const char* sql = "SELECT id, name, math, english FROM grade;";
    Scores scores;
    rc = sqlite3_exec(db, sql, callback, &scores, &errmsg);
    if (rc != SQLITE_OK) {
        cerr << "SQL error: " << errmsg << endl;
        sqlite3_free(errmsg);
    } else {
        cout << "Records selected successfully." << endl;
        cout << "수학 총점: " << scores.totalMath << ", 평균: " << (double)scores.totalMath / scores.studentCount << endl;
        cout << "영어 총점: " << scores.totalEnglish << ", 평균: " << (double)scores.totalEnglish / scores.studentCount << endl;
    }

    // 데이터베이스 닫기
    sqlite3_close(db);
    return 0;
}
