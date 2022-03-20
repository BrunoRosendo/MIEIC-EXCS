package buckets;

class Bucket {
    private final int capacity;
    private final int quantity;

    public Bucket(int capacity, int quantity) {
        this.capacity = capacity;
        this.quantity = quantity;
    }

    public int getCapacity() {
        return capacity;
    }

    public int getQuantity() {
        return quantity;
    }

    public Bucket filled() {
        return new Bucket(this.capacity, this.capacity);
    }

    public Bucket empty() {
        return new Bucket(this.capacity, 0);
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == this) {
            return true;
        }

        if (!(obj instanceof Bucket)) {
            return false;
        }

        Bucket b = (Bucket) obj;

        return this.capacity == b.getCapacity()
                && this.quantity == b.getQuantity();
    }
}
