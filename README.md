# LazyWriter - Python Package

LazyWriter is a Python application designed to simulate a typing experience with the ability to introduce small delays, potential errors, and interruptions during text entry. It uses a GUI built with PyQt6 and allows users to select different writing profiles to control the speed and accuracy of the typing. The application is built to be both fun and interactive, offering a simulation of human-like typing with errors and pauses.

## Features

- **Interactive GUI**: Built with PyQt6, it provides an intuitive user interface for controlling the typing process.
- **Customizable Profiles**: Choose from different typing profiles that affect the speed, accuracy, and error rates during the typing simulation.
- **Text Entry Simulation**: Simulate typing by controlling various factors like typing speed, chance of failure, and pauses between words and characters.
- **Error Simulation**: The program can simulate errors, including extra characters, incorrect characters, and missed characters.
- **Real-time Feedback**: The application provides a visual interface to track the progress and stop the typing process anytime.

## Installation

To use **LazyWriter**, you need to have Python 3.6+ installed along with the necessary dependencies. You can install the required packages using `pip`:

```bash
pip install pynput PyQt6
```

## How to Use

1. **Run the Application**:
   Launch the application by running the following Python script:

   ```bash
   python lazy_writer.py
   ```

2. **Select a Profile**:
   In the GUI, you can select from three typing profiles:
   - **Neuneu**: A slow, error-prone typing profile.
   - **Normal**: A standard typing speed and error rate.
   - **HyperActif**: A fast typing profile with a higher chance of mistakes.

3. **Start Typing**:
   - Enter or paste your text into the text input field.
   - Click the "Write Text!" button to start the typing simulation.
   - Click the "Stop Writing" button to interrupt the typing process at any time.

4. **Watch for Errors**:
   As the text is being typed, you may see random errors introduced based on the selected profile. These could be:
   - Extra characters.
   - Incorrect characters.
   - Missing characters.

5. **Pause and Delays**:
   The program introduces small delays between typing characters and words, simulating real human typing behavior.

## Code Overview

### Main Window

The `MainWindow` class creates the main GUI window. It includes the following key elements:
- **Text Input**: A `QTextEdit` widget where the user enters the text to be typed.
- **Start/Stop Buttons**: Buttons to start and stop the typing simulation.
- **Profile Selector**: A dropdown menu for selecting a typing profile.

### Profile Class

The `Profile` class defines the parameters for the typing simulation. These parameters include:
- `min_time_delay` and `max_time_delay`: Control the speed of typing.
- `chance_char`, `chance_word`: Determine the likelihood of taking a break between characters and words.
- `chance_to_fail_writing`: The chance of making an error during typing.
- `chance_to_see_error`: The chance that an error will be noticed and corrected.

### WriteTask Class

The `WriteTask` class is a `QThread` that simulates typing text in a separate thread. It uses the `pynput` module to control the keyboard and simulate typing.

Key methods:
- **write_text**: Handles the writing of the entire text.
- **write_char**: Types individual characters.
- **write_word**: Types words with optional delays and errors.
- **delete_word**: Simulates deleting a word with corresponding pauses.

### GUI Interaction

The application listens for button clicks and dropdown changes. When the user clicks "Write Text!", it triggers the start of the typing simulation in a separate thread. If the user clicks "Stop Writing", the current task is interrupted.

## Example Usage

Here's an example of how to run the application:

```python
import sys
from PyQt6.QtWidgets import QApplication
from lazy_writer_raphael_senellart.window import MainWindow

def main():    
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())

if __name__ == "__main__":
    main()
```

### Customizing the Typing Profile

The `Profile` class allows for creating custom profiles. You can adjust parameters such as the typing speed, error rates, and more to tailor the simulation to your needs.

Example of creating a custom profile:

```python
custom_profile = Profile(
    min_time_delay=100000, 
    max_time_delay=200000, 
    chance_char=150, 
    min_time_char=100000, 
    max_time_char=6000000,
    chance_word=30, 
    min_time_word=100000, 
    max_time_word=4000000, 
    chance_to_fail_writing=70, 
    chance_to_see_error=3
)
```

## Contributing

Feel free to contribute to LazyWriter by forking the repository, making your changes, and submitting a pull request. Suggestions and improvements are welcome!

## License

This project is licensed under the MIT License - see the LICENSE file for details.

---
