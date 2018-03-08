#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define MAX_QUEUE_SIZE 100

typedef struct {
    int id; // �� ���� ��ȣ. ������ ������� ��ȣǥ�� �޴´ٰ� �����ϸ� �ȴ�.
    int arrival_time; // �� ���� �ð�
    int service_time; // ������ �ɸ��� ���� �ð�
} data;

typedef struct {
    data queue[MAX_QUEUE_SIZE];
    int front;
    int rear;
} QueueType;

QueueType q; // ���� ������ ����

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
    //0~1�� ��ȯ
}

int duration = 10; // �� �ùķ��̼� �ð�
double arrival_prob = 0.7; // �� ���� Ȯ��
int max_serv_time = 5; // �ִ� ���� �ð�
int q_clock; // ���� �ùķ��̼� �ð�

int customers; // �մ� ��
int served_customers; // ���� ���� �մ� ��
int waited_time; // ��� �ð�

int arrive(){
    if (Frand() < arrival_prob) { return TRUE; }
    return FALSE;
}

void insert_customer(int arrival_time){
    data customer;
    customer.id = customers++;
    customer.arrival_time = arrival_time;
    // ���� �ð� = 1,2,3,4,5 �߿� �ϳ��� ���õȴ�
    customer.service_time = (int)(max_serv_time * Frand()) + 1;
    putqu(&q, customer);
    printf("����ȣ [%d]�� %d�п� �����߽��ϴ�. ���� �ð��� %d���Դϴ�.\n",
           customer.id,customer.arrival_time,customer.service_time);
}

// ��� ���� ���� �Ѹ� ������ ���񽺸� �����Ѵ�
int Outct(){
    data customer;
    int service_time;

    if (is_empty(&q)) return 0; // ��ٸ��� ���� ����
    customer = delqu(&q);
    service_time = customer.service_time - 1;
    served_customers++;

    waited_time += q_clock - customer.arrival_time; // ����ð� - �����ð�
    printf("����ȣ [%d]�� %d�п� ���񽺸� �����մϴ�. ���ð��� %d���̾����ϴ�.\n",customer.id, q_clock, q_clock-customer.arrival_time);

    return service_time;
}

void print_stat(){
    printf("���� ���� �� �� = %d\n",served_customers);
    printf("��ü ��� �ð� = %d��\n",waited_time);
    printf("1�δ� ��� ��� �ð� = %f��\n",(double)waited_time/served_customers);
    printf("���񽺸� ���� ���ϰ� ��� ���� �� �� = %d\n",customers-served_customers);
}

void print_start(){
    printf("�� �ùķ��̼� �ð�: ");scanf("%d",&duration);
    printf("�� ���� Ȯ��(0~1): ");scanf("%lf",&arrival_prob);
    printf("�ִ� ���� �ð�: ");scanf("%d",&max_serv_time);
}

int main(){
    srand(time(NULL));
    int service_time = 0;
    q_clock = 0;
    print_start();
    while (q_clock < duration) {
        q_clock++;
        printf("���� �ð�=%d\n",q_clock);
        if (arrive()) {insert_customer(q_clock); }
        if (service_time > 0) { service_time--; }// �Ѹ��� ���� ��� ó���� ������ �ٸ� ���� ���� �ʴ´�
        else { service_time = Outct(); }
    }

    print_stat();
    return 0;
}
