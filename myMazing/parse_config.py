#!/usr/bin/env python3

"""
Config parser and validator for A-Maze-ing project.
Handles reading config.txt with full validation per project specs.
"""

import sys
import os
from typing import Dict, Any


def parse_config(config_path: str) -> Dict[str, Any]:
    """
    Parse and fully validate the configuration file per project requirements.

    Args:
        config_path: Path to config file (e.g., 'config.txt').

    Returns:
        Dict[str, Any]: Validated config values.

    Raises:
        SystemExit: With clear error message on any validation failure.
    """
    config: Dict[str, Any] = {}

    # Check file existence first
    if not os.path.isfile(config_path):
        print(f"Error: Configuration file '{config_path}' not found.", file=sys.stderr)
        sys.exit(1)

    try:
        with open(config_path, "r", encoding="utf-8") as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                # Skip empty lines and comments
                if not line or line.startswith("#"):
                    continue

                # Skip malformed lines gracefully
                if "=" not in line:
                    continue

                key, value = line.split("=", 1)
                key = key.strip().upper()
                value = value.strip()

                # Parse known keys with type conversion
                if key == "WIDTH":
                    config[key] = int(value)
                elif key == "HEIGHT":
                    config[key] = int(value)
                elif key == "ENTRY":
                    config[key] = tuple(map(int, value.split(",")))
                elif key == "EXIT":
                    config[key] = tuple(map(int, value.split(",")))
                elif key == "OUTPUT_FILE":  # Match project spec (no underscore)
                    config[key] = value
                elif key == "PERFECT":
                    config[key] = value.lower() in ("true", "1", "yes")
                elif key == "SEED":
                    config[key] = int(value)

    except ValueError as e:
        print(f"Error parsing configuration value: {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"Unexpected error reading config: {e}", file=sys.stderr)
        sys.exit(1)

    # Validate mandatory keys present
    mandatory = ["WIDTH", "HEIGHT", "ENTRY", "EXIT", "OUTPUT_FILE", "PERFECT"]
    missing = [key for key in mandatory if key not in config]
    if missing:
        print(f"Error: Missing required keys: {', '.join(missing)}", file=sys.stderr)
        sys.exit(1)

    # Bounds and logic validation
    width, height = config["WIDTH"], config["HEIGHT"]
    entry, exit_pos = config["ENTRY"], config["EXIT"]

    # Positive dimensions
    if config["WIDTH"] <= 0 or config["HEIGHT"] <= 0:
        print("Error: WIDTH and HEIGHT must be positive integers", file=sys.stderr)
        sys.exit(1)

    # Coordinates in bounds
    for pos, name in [(entry, "ENTRY"), (exit_pos, "EXIT")]:
        if not (0 <= pos[0] < width and 0 <= pos[1] < height):
            print(
                f"Error: {name} {pos} out of maze bounds (0-{width - 1}, 0-{height - 1})",
                file=sys.stderr,
            )
            sys.exit(1)

    # Entry != Exit
    if entry == exit_pos:
        print("Error: ENTRY and EXIT must be different positions", file=sys.stderr)
        sys.exit(1)

    # Maze size warning for 42 pattern
    if width < 5 or height < 5:
        print("WARNING: Maze too small for 42 pattern (will be omitted)")

    return config


def main() -> None:
    """Entry point: validate CLI args and config."""
    if len(sys.argv) != 2:
        print("USAGE: python3 amazeing.py config.txt", file=sys.stderr)
        sys.exit(1)

    config = parse_config(sys.argv[1])

    print("SUCCESS: Config validated!")
    print(f"Maze: {config['WIDTH']}x{config['HEIGHT']}")
    print(f"Entry: {config['ENTRY']}, Exit: {config['EXIT']}")
    print(f"Perfect: {config['PERFECT']}, Output: {config['OUTPUT_FILE']}")
    # TODO: Initialize MazeGenerator(config), generate, visualize


if __name__ == "__main__":
    main()
