package model;

public class Bandage extends Medicine {

    protected double coefficientOfStretching;

    public double getCoefficientOfStretching() {
        return coefficientOfStretching;
    }

    protected double lenght;

    public double getLenght() {
        return lenght;
    }

    public void cutPart(double lenght) {
        if (this.lenght < lenght) {
            throw new IllegalArgumentException();
        }
        this.lenght -= lenght;
    }

    @Override
    public void someWork() {

    }
}
