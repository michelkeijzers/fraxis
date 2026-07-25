// void MenuStates::UpdateForMsPassed()
// {
//     auto now = std::chrono::steady_clock::now();
//     uint64_t elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - _timeInCurrentState).count();

//     switch (_currentState)
//     {
//     case State::S000_WELCOME: UpdateS000ForMsPassed(elapsedMs); break;
//     default: /* ignore others */ break;
//     }
// }

// void MenuStates::UpdateS000ForMsPassed(uint64_t elapsedMs)
// {
//     if (elapsedMs >= 2000)
//     {
//         _currentState = State::S010_SELECT_APP_TYPE;
//     }
// }


