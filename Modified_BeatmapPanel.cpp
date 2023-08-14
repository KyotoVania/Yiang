/*
** EPITECH PROJECT, 2023
** Yiang
** File description:
** beatmappanell.cpp
*/

#include "GraphicElement/BeatmapPanel.hpp"
#include <cmath>


BeatmapPanel::BeatmapPanel(){

}

BeatmapPanel::BeatmapPanel(const sf::Texture& texturePanel, const sf::Texture& textureCover, const sf::Vector2f& position, std::pair<int, int> res, const BeatmapConfig& beatmapConfig, const sf::Font& fonts) {
    // Normalize the position
    float normalizedX = std::fmod(position.x, 10.0f) / 10.0f;
    float normalizedY = std::fmod(position.y, 10.0f) / 10.0f;

    // Calculate the screen position
    float screenX = normalizedX * res.first - texturePanel.getSize().x / 2;
    float screenY = normalizedY * res.second - texturePanel.getSize().y / 2;

    sprite.setTexture(texturePanel);
    sprite.setPosition(screenX, screenY);
    // Initialize left arrow button
    sf::Texture leftArrowTexture;
    leftArrowTexture.loadFromFile("Resources/UI/ArrowsLeft.png");
    leftArrowButton.setTexture(leftArrowTexture);
    leftArrowButton.setPosition(screenX, screenY + sprite.getGlobalBounds().height - leftArrowTexture.getSize().y - 10);  // Place it at the bottom left of the panel with a small margin

    // Initialize right arrow button
    sf::Texture rightArrowTexture;
    rightArrowTexture.loadFromFile("Resources/UI/ArrowsRight.png");
    rightArrowButton.setTexture(rightArrowTexture);
    rightArrowButton.setPosition(screenX + sprite.getGlobalBounds().width - rightArrowTexture.getSize().x, screenY + sprite.getGlobalBounds().height - rightArrowTexture.getSize().y - 10);  // Place it at the bottom right of the panel with a small margin

    currentDifficulty = 0;  // Initial difficulty level

    std::cout << "Creating panel position : " << screenX << " " << screenY << std::endl;
    std::cout << "position are set to : " << position.x << " " << position.y << std::endl;
    this->position = sf::Vector2f(screenX, screenY);
    // Assuming the cover is a smaller sprite displayed on the panel
    coverSprite.setTexture(textureCover);
    coverSprite.setPosition(position); // Adjust this as needed
    std::cout << "Creating grade text" << std::endl;
    // Assuming grade is a text displayed on the panel
    //load font "Resources/Fonts/sansation.ttf"
    textSize = 35;
    // Calculate the starting position for the text based on the cover's right edge
    float textStartX = coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + 10; // 10 is a margin, adjust as needed
    float textStartY = coverSprite.getPosition().y;

    // Set up the text elements
    titleText.setFont(fonts);
    titleText.setCharacterSize(20); // Adjust as needed
    titleText.setString("Title : " + beatmapConfig.getName());
    titleText.setPosition(textStartX, textStartY);

    artistText.setFont(fonts);
    artistText.setCharacterSize(20); // Adjust as needed
    artistText.setString("Artist : " + beatmapConfig.getArtist());
    artistText.setPosition(textStartX, textStartY + titleText.getGlobalBounds().height + 5); // 5 is spacing between texts

    difficultyText.setFont(fonts);
    difficultyText.setCharacterSize(20); // Adjust as needed
    difficultyText.setString("Difficulty : " + std::to_string(beatmapConfig.getDifficulty()));
    difficultyText.setPosition(textStartX, artistText.getPosition().y + artistText.getGlobalBounds().height + 5);

    gradeText.setFont(fonts);
    gradeText.setCharacterSize(20); // Adjust as needed
    gradeText.setString("Grade : S");
    gradeText.setPosition(textStartX, difficultyText.getPosition().y + difficultyText.getGlobalBounds().height + 5);

}

BeatmapPanel::~BeatmapPanel(){

}

void BeatmapPanel::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(coverSprite);
    /*
    gradeText.setFont(_font);
    titleText.setFont(_font);
    artistText.setFont(_font);
    difficultyText.setFont(_font);
     */
    window.draw(titleText);
    window.draw(artistText);
    window.draw(difficultyText);
    // Draw difficulty buttons
    window.draw(leftArrowButton.getSprite());
    window.draw(rightArrowButton.getSprite());

    window.draw(gradeText);
    //       std::cout << "Drawing panel" << std::endl;
}

void BeatmapPanel::setText(const std::string& text, const sf::Font& font, unsigned int characterSize) {
    gradeText.setString(text);
    gradeText.setFont(font);
    gradeText.setCharacterSize(characterSize);
    // Center the text in the button
    sf::FloatRect textRect = gradeText.getLocalBounds();
    gradeText.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    gradeText.setPosition(sf::Vector2f(position.x + size.x/2.0f, position.y + size.y/2.0f));
}

void BeatmapPanel::adjustPanel(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {

}

void BeatmapPanel::adjustCover(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {
}
void BeatmapPanel::adjustGrade(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {
}
void BeatmapPanel::adjust(float scale, float opacity, const sf::Vector2f& offset, std::pair<int, int> res) {
    //we need to split the res by 10 to get the real resolution
    float screenOffsetX = std::fmod(offset.x, 10.0f) / 10.0f * res.first;
    float screenOffsetY = std::fmod(offset.y, 10.0f) / 10.0f * res.second;
    float PercentX = res.first / 100.0f;
    float PercentY = res.second / 100.0f;
    //std::cout << "PercentX : " << PercentX << " PercentY : " << PercentY << std::endl;
    // Adjust the panel
    sprite.setScale(scale, scale);
    sprite.setColor(sf::Color(255, 255, 255, opacity));
    screenOffsetX = screenOffsetX - (sprite.getTexture()->getSize().x * scale) / 2;
    screenOffsetY = screenOffsetY - (sprite.getTexture()->getSize().y * scale) / 2;
    sprite.setPosition(screenOffsetX, screenOffsetY); // Also set the position to the screen offset
    // Adjust the cover and text as well
    coverSprite.setScale(scale, scale);
    coverSprite.setColor(sf::Color(255, 255, 255, opacity));
    coverSprite.setPosition(screenOffsetX + PercentX * 5, screenOffsetY + PercentY * 5); // Also set the position to the screen offset
    gradeText.setCharacterSize(textSize * scale);
    titleText.setCharacterSize(textSize * scale);
    artistText.setCharacterSize(textSize * scale);
    difficultyText.setCharacterSize(textSize * scale);
    titleText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, coverSprite.getPosition().y);
    artistText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, titleText.getPosition().y + PercentY * 3);
    difficultyText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, artistText.getPosition().y + PercentY * 3);
    gradeText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + PercentX, difficultyText.getPosition().y + PercentY * 3);
    //difficultyText.setPosition(artistText.getPosition().x, artistText.getPosition().y + artistText.getGlobalBounds().height + 5);
    //gradeText.setPosition(coverSprite.getPosition().x + coverSprite.getGlobalBounds().width + 10, coverSprite.getPosition().y + coverSprite.getGlobalBounds().height - gradeText.getGlobalBounds().height);
}

void BeatmapPanel::handleButtonClick(const sf::Vector2f& mousePosition) {
    if (leftArrowButton.isClicked(mousePosition)) {
        if (currentDifficulty > 0) {
            currentDifficulty--;
            // Update the difficultyText or any other required elements
        }
    } else if (rightArrowButton.isClicked(mousePosition)) {
        if (currentDifficulty < MAX_DIFFICULTY) {  // Assuming MAX_DIFFICULTY is a defined constant or you can replace with the desired value
            currentDifficulty++;
            // Update the difficultyText or any other required elements
        }
    }
}
