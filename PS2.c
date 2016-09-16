// Sol1
#define BOY 	0
#define GIRL 	1

typedef struct{
	spinlock_t lock;
	int count[2];			// count[1] girl, count[0] boy
} boygirl_lock_t;

void boygirl_lock_init(boygirl_lock_t *lock){
	spin_lock_init(lock->lock);
	lock->count[0] =0;
	lock->count[1] =0;
}
void boygirl_lock(boygirl_lock_t *lock,int gender){
	while(1){
		spin_lock_irq(&(lock->lock));
		if(gender==0 && lock->count[1] == 0){
			count[0]++;
			break;
		}
		if(gender == 1 && lock->count[0] == 0){
			count[1]++;
			break;
		}
		spin_unlock_irq(&(lock->lock));
	}
	spin_unlock_irq(&(lock->lock));
	return;
}

void boygirl_unlock(boygirl_lock_t *lock,int gender){
	while(1){
		spin_lock_irq(&(lock->lock));
		if(gender==0 && lock->count[0] > 0){
			count[0]--;
			break;
		}
		if(gender == 1 && lock->count[1] > 0){
			count[1]--;
			break;
		}
		spin_unlock_irq(&(lock->lock));
	}
	spin_unlock_irq(&(lock->lock));
	return;
}


// Sol2
#define BOY 0
#define GIRL 1

typedef struct {
	spinlock_t lock;
	int count[2];
} boygirl_lock_t;

void boygirl_lock_init(boygirl_lock_t *lock) {
	lock->lock = SPIN_LOCK_UNLOCKED;
	lock->count[BOY] = 0;
	lock->count[GIRL] = 0;
	return;
}

void boygirl_lock(boygirl_lock_t *lock, int gender) {
	spin_lock_irq(&(lock->lock));
	while (lock->count[1-gender]) {
		spin_unlock_irq(&(lock->lock));
		spin_lock_irq(&(lock->lock));
	}
	lock->count[gender] ++;
	spin_unlock_irq(&(lock->lock));
	return;
}

void boygirl_unlock(boygirl_lock_t *lock, int gender) {
	spin_lock_irq(&(lock->lock));
	lock->count[gender] --;
	spin_unlock_irq(&(lock->lock));
	return;
}
