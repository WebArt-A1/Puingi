#include <Arduino.h>
#include <set>

// Размер генерации
const unsigned long totalKeys = 0xFFFFFFFF;  // Всего 4,294,967,296 ключей (32 бита)
unsigned long generatedKeys = 0;  // Сколько ключей уже сгенерировано

// Интервал вывода прогресса
const int progressInterval = 5000;  // Прогресс и вопрос каждые 5000 сгенерированных ключей

// Функция для генерации случайных ИК кодов
unsigned long generateRandomKey() {
  return random(0x00000000, 0xFFFFFFFF);  // Генерация случайного 32-битного числа
}

// Функция для расчета оставшегося времени
String formatTime(unsigned long milliseconds) {
  unsigned long hours = milliseconds / 3600000;
  unsigned long minutes = (milliseconds % 3600000) / 60000;
  unsigned long seconds = (milliseconds % 60000) / 1000;
  return String(hours) + "h " + String(minutes) + "m " + String(seconds) + "s";
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));  // Инициализация генератора случайных чисел

  Serial.println("Generating random IR codes...");

  unsigned long startTime = millis();  // Засекаем время начала
  std::set<unsigned long> generatedSet;  // Множество для хранения уникальных сгенерированных ключей

  while (generatedKeys < totalKeys) {
    unsigned long newKey = generateRandomKey();

    // Проверка, был ли ключ уже сгенерирован в этом цикле
    while (generatedSet.count(newKey) > 0) {
      // Если ключ уже есть, генерируем новый
      newKey = generateRandomKey();
    }

    // Добавляем уникальный ключ в множество
    generatedSet.insert(newKey);
    generatedKeys++;

    // Периодический вывод прогресса и вопросов
    if (generatedKeys % progressInterval == 0) {
      unsigned long elapsedTime = millis() - startTime;  // Время, прошедшее с начала
      unsigned long remainingKeys = totalKeys - generatedKeys;  // Оставшиеся ключи

      // Расчёт приблизительного оставшегося времени
      unsigned long estimatedTime = (elapsedTime * remainingKeys) / generatedKeys;

      Serial.print("Generated ");
      Serial.print(generatedKeys);
      Serial.print(" IR codes... ");
      Serial.print("Remaining: ");
      Serial.print(remainingKeys);
      Serial.print(" keys. ");
      Serial.print("Estimated time remaining: ");
      Serial.println(formatTime(estimatedTime));

      // Задаём вопрос: был ли этот ключ в этом цикле
      Serial.println("Was this key in this cycle? (Y/N): ");
      // В реальной программе можно использовать Serial.read() для получения ввода пользователя
    }
  }

  unsigned long totalTime = millis() - startTime;
  Serial.print("Generation complete. Total time: ");
  Serial.println(formatTime(totalTime));
}

void loop() {
  // Основной код остаётся пустым, поскольку вся генерация происходит в setup
}
