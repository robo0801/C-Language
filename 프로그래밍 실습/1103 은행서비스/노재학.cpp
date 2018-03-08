#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define MAX_QUEUE_SIZE 100

typedef struct {
    int id; // 고객 고유 번호. 들어오는 순서대로 번호표를 받는다고 생각하면 된다.
    int arrival_time; // 고객 도착 시간
    int service_time; // 고객에게 걸리는 서비스 시간
} data;

typedef struct {
    data queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

QueueType q; // 전역 변수로 설정

void error(char *mes){ fprintf(stderr, "%s\n", mes); exit(1); }

void init(QueueType *q){ q->front = 0; q->rear = 0; }
int is_empty(QueueType *q){ return q->front == q->rear; }
int is_full(QueueType *q){ return (q->rear+1) % MAX_QUEUE_SIZE == q->front; }

void putqu(QueueType *q, data item){
    if (is_full(q)) { error("q is full\n"); }
    q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
    q->queue[q->rear] = item;
}

data delqu(QueueType *q){
    if (is_empty(q)) { error("q is empty\n"); }
    q->front = (q->front+1) % MAX_QUEUE_SIZE;
    return q->queue[q->front];
}

data peek(QueueType *q){
    if (is_empty(q)) { error("q is empty\n"); }
    return q->queue[q->front];
}

double Frand(){
    return rand() / (double) RAND_MAX;
    //0~1갑 반환
}

int duration = 10; // 총 시뮬레이션 시간
double arrival_prob = 0.7; // 고객 도착 확률
int max_serv_time = 5; // 최대 서비스 시간
int q_clock; // 현재 시뮬레이션 시간

int customers; // 손님 수
int served_customers; // 서비스 받은 손님 수
int waited_time; // 대기 시간

int arrive(){
    if (Frand() < arrival_prob) { return TRUE; }
    return FALSE;
}

void insert_customer(int arrival_time){
    data customer;
    customer.id = customers++;
    customer.arrival_time = arrival_time;
    // 서비스 시간 = 1,2,3,4,5 중에 하나가 선택된다
    customer.service_time = (int)(max_serv_time * Frand()) + 1;
    putqu(&q, customer);
    printf("고객번호 [%d]이 %d분에 도착했습니다. 서비스 시간은 %d분입니다.\n",
           customer.id,customer.arrival_time,customer.service_time);
}

// 대기 중인 고객을 한명 꺼내서 서비스를 실행한다
int Outct(){
    data customer;
    int service_time;

    if (is_empty(&q)) return 0; // 기다리는 고객이 없다
    customer = delqu(&q);
    service_time = customer.service_time - 1;
    served_customers++;

    waited_time += q_clock - customer.arrival_time; // 현재시간 - 도착시간
    printf("고객번호 [%d]이 %d분에 서비스를 시작합니다. 대기시간은 %d분이었습니다.\n",customer.id, q_clock, q_clock-customer.arrival_time);

    return service_time;
}

void print_stat(){
    printf("서비스 받은 고객 수 = %d\n",served_customers);
    printf("전체 대기 시간 = %d분\n",waited_time);
    printf("1인당 평균 대기 시간 = %f분\n",(double)waited_time/served_customers);
    printf("서비스를 받지 못하고 대기 중인 고객 수 = %d\n",customers-served_customers);
}

void print_start(){
    printf("총 시뮬레이션 시간: ");scanf("%d",&duration);
    printf("고객 도착 확률(0~1): ");scanf("%lf",&arrival_prob);
    printf("최대 서비스 시간: ");scanf("%d",&max_serv_time);
}

int main(){
    srand(time(NULL));
    int service_time = 0;
    q_clock = 0;
    print_start();
    while (q_clock < duration) {
        q_clock++;
        printf("현재 시각=%d\n",q_clock);
        if (arrive()) {insert_customer(q_clock); }
        if (service_time > 0) { service_time--; }// 한명의 고객이 모두 처리될 때까지 다른 고객을 받지 않는다
        else { service_time = Outct(); }
    }

    print_stat();
    return 0;
}
