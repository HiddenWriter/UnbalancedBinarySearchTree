#pragma once
class App
{
public:
	App()
		: mCommand(-1)
	{}
	App(const App&) = delete;
	App& operator=(const App&) = delete;
	~App();

	void Run();
	void Add();
	void Delete();
	
	void Print() noexcept;
	void Height() noexcept;
	void ShowSize() noexcept;
private:
	TYPE& GetType(void) noexcept;
	void Destroy();
private:
	void* vt;
	int mCommand;
};