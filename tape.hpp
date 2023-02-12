class Tape {
	struct Node {
		explicit Node(const unsigned char data) : 
			data_(data), 
			back(nullptr),
			next(nullptr) {}

		unsigned char data_;
		Node* back;
		Node* next;
	};

public:
	explicit Tape() = default;
	~Tape();

	void incrementHead() noexcept;
	void decrementHead() noexcept;

	void moveLeft() noexcept;
	void moveRight() noexcept;	

	void setHeadData(const unsigned char input) noexcept;
	constexpr unsigned char getHeadData() const noexcept { return tapeHead->data_; }

private:
	Node* tapeHead = new Node(0);
};
