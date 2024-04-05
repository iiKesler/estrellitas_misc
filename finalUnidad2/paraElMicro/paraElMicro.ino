void task()
{
    enum class TaskStates
    {
        INIT,
        WAIT_INIT,
        SEND_EVENT
    };
    static TaskStates taskState = TaskStates::INIT;
    static uint32_t previous = 0;
    static uint32_t toPrint = 3;
    static uint32_t previousTime = 0;
    static bool ledState = true;
  
    uint32_t currentTime = millis();

  if( (currentTime - previousTime) > 100){
    previousTime = currentTime;
    ledState = !ledState;
    digitalWrite(LED_BUILTIN, ledState);
  }

    switch (taskState)
    {
        case TaskStates::INIT:
        {
            Serial.begin(115200);
            taskState = TaskStates::WAIT_INIT;
            break;
        }
        case TaskStates::WAIT_INIT:
        {
            if (Serial.available() > 0)
            {
                if (Serial.read() == '1')
                {
                    previous = 0; // Force to send the first value immediately
                    taskState = TaskStates::SEND_EVENT;
                }
            }
            break;
        }
        case TaskStates::SEND_EVENT:
        {
            uint32_t current = millis();
            if ((current - previous) > 3000)
            {
                previous = current;
                Serial.print(toPrint);
                toPrint=toPrint+3;
            }
            if (Serial.available() > 0)
            {
                if (Serial.read() == '2')
                {
                    taskState = TaskStates::WAIT_INIT;
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
    task();
}

void loop()
{
  
    task();
}
