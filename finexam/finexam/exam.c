// linked_list.c (slide 62)
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT 100

typedef struct Student{
	int number;
	char name[12];
	int korean;
	int english;
	int math;
	int total;
	double average;
	int rank;
	struct Node* p_next; // 다음 노드를 가리킬 포인터
} Student;
void loadData(Student students[], int* count, const char* filename);
void saveData(Student students[], int count, const char* filename);
void addStudent(Student students[], int* count);
void showGrades(Student students[], int count);

/*void AddNumber(Node** pp_head, Node** pp_tail, int data) {
	if (NULL != *pp_head) {
		(*pp_tail)->p_next = (Node*)malloc(sizeof(Node)); // 새 노드를 할당
		*pp_tail = (*pp_tail)->p_next; // p_tail(*pp_tail)에 새 노드의 주소 값을 저장
	}
	else {
		// *p_head 값이 NULL이라서 첫 노드가 추가됨. p_head 값에 직접 대입함
		*pp_head = (Node*)malloc(sizeof(Node));
		*pp_tail = *pp_head; // 새 노드의 주소 값을 p_tail(*pp_tail)에 저장
	}
	(*pp_tail)->number = data; // 새 노드의 number에 data 값을 저장
	(*pp_tail)->p_next = NULL; // 다음 노드가 없음을 명시함 
}*/

int main(void) {
	// 노드의 시작과 끝을 기억할 포인터
	//Node* p_head = NULL, * p_tail = NULL, * p;
	
	Student students[MAX_STUDENT];
	int studentCount = 0;
	int choice;
	const char* filename = "students.dat";

	// 무한 루프: 중간에 9999를 누르면 종료함
	while (1) {
		
		
		printf("\n[Menu]\n");
		printf("1. .dat 파일에서 데이터 읽기\n");
		printf("2. 추가 학생 정보 입력\n");
		printf("3. .dat 파일 저장\n");
		printf("4. 성적 확인\n");
		printf("5. 종료\n");
		printf("-------------------\n");
		printf("선택(1~5): ");
		scanf_s("%d", &choice);
		getchar();
		switch (choice) {
		case 1:
			loadData(students, &studentCount, filename);
			break;
		case 2:
			addStudent(students, &studentCount);
			break;
		case 3:
			saveData(students, studentCount, filename);
			break;
		case 4:
			showGrades(students, studentCount);
			break;
		case 5:
			printf("프로그램 종료.\n");
			exit(0);
		default:
			printf("잘못된 선택입니다. 1~5 중에서 선택하세요.\n");
		}
	}
	return 0;
}
		// 노드의 시작과 끝을 기억하는 포인터의 주소 값과 입력된 숫자를 전달
		//AddNumber(&p_head, &p_tail, temp);
	

	// 입력된 숫자를 출력하기 위해서 노드를 탐색할 포인터에 
	// 시작 노드의 주소 값을 대입합니다.
	/*p = p_head;
	while (NULL != p) {
		if (p != p_head)
			printf(" + "); // 숫자와 숫자 사이에 + 출력

		printf("%d", p->number);

		info = info + p->number; // sum += p->number하면...?
		p = p->p_next; // 다음 노드로 이동
	}
	printf(" = %d\n", sum);

	// 사용한 모든 노드를 삭제합니다. 
	while (NULL != p_head) {
		p = p_head; // 현재 노드를 삭제하기 위해 p 변수에 노드 주소 값을 저장
		p_head = p_head->p_next; // 시작 위치를 다음 노드로 
		free(p); // 기억했던 주소를 사용하여 노드를 삭제함
	}
	p_tail = p_head; // 반복문을 나오면 p_head 값은 NULL. p_tail 값도 NULL로 변경*/




// .dat 파일에서 데이터 읽기
void loadData(Student students[], int* count, const char* filename) {
	FILE* fp = fopen(filename, "rb");
	if (!fp) {
		printf(".dat 파일을 열 수 없습니다.\n");
		return;
	}

	*count = fread(students, sizeof(Student), MAX_STUDENT, fp);
	fclose(fp);
	printf("%d명의 학생 데이터를 불러왔습니다.\n", *count);
}

// 데이터 저장
void saveData(Student students[], int count, const char* filename) {
	FILE* fp = fopen(filename, "wb");
	if (!fp) {
		printf(".dat 파일을 생성할 수 없습니다.\n");
		return;
	}

	fwrite(students, sizeof(Student), count, fp);
	fclose(fp);
	printf("%d명의 학생 데이터를 저장했습니다.\n", count);
}

// 학생 정보 입력
void addStudent(Student students[], int* count) {
	if (*count >= MAX_STUDENT) {
		printf("더 이상 학생을 추가할 수 없습니다.\n");
		return;
	}

	Student s;
	printf("학생 이름: ");
	fgets(s.name, sizeof(s.name), stdin);
	s.name[strcspn(s.name, "\n")] = 0; // 개행 제거

	printf("국어 점수: "); scanf_s("%d", &s.korean);
	printf("영어 점수: "); scanf_s("%d", &s.english);
	printf("수학 점수: "); scanf_s("%d", &s.math);
	getchar(); // 개행 제거

	s.total = s.korean + s.english + s.math;
	s.average = s.total / 3.0;
	s.rank = 0; // 등수는 나중에 계산

	students[*count] = s;
	(*count)++;
	printf("학생 정보가 추가되었습니다.\n");
}

// 성적 확인
void showGrades(Student students[], int count) {
	if (count == 0) {
		printf("저장된 학생 정보가 없습니다.\n");
		return;
	}

	// 등수 계산 (총점 기준 내림차순)
	for (int i = 0; i < count; i++) {
		students[i].rank = 1; // 초기 등수 1
		for (int j = 0; j < count; j++) {
			if (students[j].total > students[i].total) {
				students[i].rank++;
			}
		}
	}

	printf("\n이름\t국어\t영어\t수학\t총점\t평균\t등수\n");
	printf("----------------------------------------------------\n");
	for (int i = 0; i < count; i++) {
		printf("%s\t%d\t%d\t%d\t%d\t%.2f\t%d\n",
			students[i].name,
			students[i].korean,
			students[i].english,
			students[i].math,
			students[i].total,
			students[i].average,
			students[i].rank);
	}
}