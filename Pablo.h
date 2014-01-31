#ifndef Pablo_h
#define Pablo_h

class Pablo {
  public:
    Pablo ();
    void forward(int l, int r, int t);
    void reverse(int l, int r, int t);
    void rotate(int t);
    void brake(int t);
    void march();
  private:
    void beep (unsigned char speakerPin, int frequencyInHertz, long timeInMiliseconds);
};
#endif
