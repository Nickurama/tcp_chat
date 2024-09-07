class UniqueSocket
{
public:
	explicit UniqueSocket(int sockFd);
	~UniqueSocket();
	int get() const;
	operator int() const;
private:
	UniqueSocket(const UniqueSocket&) = delete;
	UniqueSocket& operator=(const UniqueSocket&) = delete;

	int m_fd;
};
