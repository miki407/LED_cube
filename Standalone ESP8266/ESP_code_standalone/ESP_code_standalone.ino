boolean cube [10][10][10][2];
int Data = 14;
int Clock_ = 12;
int Latch = 16;

void setup() {
  // put your setup code here, to run once:
  pinMode(Data, OUTPUT);
  pinMode(Clock_, OUTPUT);
  pinMode(Latch, OUTPUT);
  //  Serial.begin(115200);
}

void loop() {
  for (int c = 0; c < 2; c++) {
    for (int x = 0; x  < 10; x++) {
      for (int y = 0; y < 10; y++) {
        for (int z = 0; z < 10; z++) {

          cube [x][y][z][c] = 1;

          output();
          
          cube [x][y][z][c] = 0;
          yield();
        }
      }
    }
  }
}
void output() {
  for (int x_ = 0 ; x_ < 10; x_++) {
    for (int c_ = 0; c_ < 2; c_++) {
      for ( int y_ = 0; y_ < 10; y_++) {

        for (int n = 0; n < 6; n++) {
          digitalWrite(Clock_, 1);
          digitalWrite(Clock_, 0);
        }

        for (int z_ = 0; z_ < 10; z_++) {
          digitalWrite(Data, cube[x_][y_][z_][c_]);
          digitalWrite(Clock_, 1);
          digitalWrite(Clock_, 0);
        }

      }
    }

    for (int n = 0; n < 6; n++) {
      digitalWrite(Clock_, 1);
      digitalWrite(Clock_, 0);
    }
    for (int n = 0; n < 10; n++) {
      if ( n == x_ ) {
        digitalWrite(Data, 1);
      }
      else {
        digitalWrite(Data, 0);
      }
      digitalWrite(Clock_, 1);
      digitalWrite(Clock_, 0);
      digitalWrite(Data, 0);
    }
    digitalWrite(Latch, 1);
    digitalWrite(Latch, 0);
  }
}
