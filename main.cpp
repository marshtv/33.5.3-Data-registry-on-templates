#include <iostream>
#include <string>
#include <vector>

template<typename T1, typename T2>
struct Pair {
	T1 key;
	T2 value;
};

template<typename T1, typename T2>
class Registry {
private:
	std::vector<Pair<T1, T2>> registry;

	Pair<T1, T2> input_pair() {
		Pair<T1, T2> _pair;
		std::cout << "Input pair:" << std::endl;
		std::cout << "key:";
		std::cin >> _pair.key;
		std::cout << "value:";
		std::cin >> _pair.value;
		return _pair;
	}

	void add() {
		registry.push_back(input_pair());
	}
public:
	Registry() = default;

	~Registry() = default;

	void load_registry() {
		std::string command = "add";
		while(command != "exit") {
			this->add();
			std::string _str;
			std::cout << R"(Type "exit" for exit or "add" to continue:)" << std::endl;
			std::cin >> _str;
			command.resize(_str.size());
			command = _str;
		}
	}

	void find(const T1& _key, std::vector<T2>& values, bool& _input) {
		if (!registry.empty()) {
			int count = 0;
			for (auto it = registry.begin(); it != registry.end(); ++it) {
				if (it->key == _key) {
					count++;
					values.push_back(it->value);
				}
			}
			if (count == 0) {
				std::cout << "This key not exist in registry!" << std::endl;
			} else
				_input = false;
		} else {
			std::cout << "Registry is EMPTY." << std::endl;
			_input = false;
		}
	}

	void remove(const T1& _key, bool& _input) {
		if (!registry.empty()) {
			int count = 0;
			for (auto it = registry.begin(); it != registry.end();) {
				if (it->key == _key) {
					count++;
					std::cout << "removing value: " << it->value << std::endl;
					registry.erase(it);
				} else
					++it;
			}
			if (count == 0) {
				std::cout << "This key not exist in registry!" << std::endl;
			} else
				_input = false;
		} else {
			std::cout << "Registry is EMPTY." << std::endl;
			_input = false;
		}
	}

	void print() {
		if (!registry.empty()) {
			for (auto it = registry.begin(); it != registry.end(); ++it) {
				std::cout << "key: " << it->key << ", value: " << it->value << std::endl;
			}
		} else {
			std::cout << "Registry is EMPTY." << std::endl;
		}
	}
};

template<typename T1, typename T2>
void find_values(Registry<T1, T2>* _registry) {
	bool input = true;
	while(input) {
		std::cout << "\nInput key for FIND all values:";
		std::vector<T2> values;
		T1 key_find;
		std::cin >> key_find;
		_registry->find(key_find, values, input);
		for (int i = 0; i < values.size(); ++i) {
			std::cout << i << ": " << values[i] << std::endl;
		}
	}
}

template<typename T1, typename T2>
void remove_values(Registry<T1, T2>* _registry) {
	bool input = true;
	while(input) {
		std::cout << "\nInput key for REMOVE all values:";
		T1 key_remove;
		std::cin >> key_remove;
		_registry->remove(key_remove, input);
	}
}

int main() {
	auto* registry_1 = new Registry<int, std::string>;
	std::cout << "\nLoad registry_1<int, std::string>:" << std::endl;
	registry_1->load_registry();
	registry_1->print();

	find_values (registry_1);

	remove_values(registry_1);

	std::cout << "\nregistry_1:" << std::endl;
	registry_1->print();

	auto* registry_2 = new Registry<std::string, double>;
	std::cout << "\nLoad registry_2<std::string, double>:" << std::endl;
	registry_2->load_registry();
	registry_2->print();

	find_values (registry_2);

	remove_values(registry_2);

	std::cout << "\nregistry_2:" << std::endl;
	registry_2->print();

	delete registry_1;
	delete registry_2;
}
