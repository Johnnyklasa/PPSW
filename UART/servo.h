enum ServoState {CALLIB, IDLE, IN_PROGRESS};
void DetectorInit(void);
enum DetectorState {ACTIVE, INACTIVE};
void Automat(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);
extern unsigned int uiCurrentPosition;

