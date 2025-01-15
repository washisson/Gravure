
sf::Image createEngravingEffect(const sf::Image& original) {
	sf::Image result;
	result.create(original.getSize().x, original.getSize().y, sf::Color::White);

	for (unsigned int x = 0; x < original.getSize().x; ++x) {
		for (unsigned int y = 0; y < original.getSize().y; ++y) {
			sf::Color pixelColor = original.getPixel(x, y);

			// ����������� � ������� ������
			int grayValue = 0.299 * pixelColor.r + 0.587 * pixelColor.g + 0.114 * pixelColor.b;

			// �������� ����� ������� ����� ������������ ���������
			// �������������� ���������
			if (y % 5 == 0 && grayValue < 128) {
				result.setPixel(x, y, sf::Color::Black);
			}

			// ������������ ��������� ����� �������
			if ((x + y) % 10 == 0 && grayValue < 200) {
				result.setPixel(x, y, sf::Color::Black);
			}

			// ������������ ��������� ������ ������
			if ((x - y) % 10 == 0 && grayValue < 64) {
				result.setPixel(x, y, sf::Color::Black);
			}
		}
	}

	return result;
}