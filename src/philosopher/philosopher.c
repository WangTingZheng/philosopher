#include "philosopher.h"


_Noreturn void *eat_think(void *arg)
{
    int phi = *(int *)arg;
    int left,right;
    left = returnLeft(phi);
    right = returnRight(phi);

    for(;;){
        sleep(rand()%4);//思考0~3秒
        pthread_mutex_lock(&forkp[left]);//拿起左手的叉子
        printf("哲学家 %d 拿起左手的叉子 %d\n", phi, left);
        if (pthread_mutex_trylock(&forkp[right]) == EBUSY){//拿起右手的叉子
            pthread_mutex_unlock(&forkp[left]);//如果右边叉子被拿走放下左手的叉子
            printf("哲学家 %d 放下左手的叉子 %d\n", phi, left);
            continue;
        }
        printf("哲学家 %d 拿起右手的叉子 %d\n", phi, right);
        printf("哲学家 %d 在吃饭\n",phi);
        printf("--------------------------------\n");
        sleep(rand()%4);//吃0~3秒
        pthread_mutex_unlock(&forkp[left]);
        pthread_mutex_unlock(&forkp[right]);
    }
}

int start(){
    pthread_t phiThread[philosopherNumber];


    for (int a = 0; a < philosopherNumber; a++)
    {
        pthread_mutex_init(&forkp[a], NULL);
        printf("thread %d inited\n", a);
    }

    for (int b = 0; b < philosopherNumber; b++)
    {
        int* temp = (int*)malloc(sizeof(int));
        *temp = b;
        pthread_create(&phiThread[b], NULL, eat_think, (void *)temp);
        printf("thread %d created\n", b);
    }

    for (int c = 0; c <philosopherNumber; c++)
        pthread_join(phiThread[c], NULL);
    return 0;
}