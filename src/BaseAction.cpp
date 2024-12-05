
#include "Action.h"

ActionStatus BaseAction::getStatus() const {
    return _status;
}

void BaseAction::complete() {
    _status = ActionStatus::COMPLETED;
}

void BaseAction::error(string errorMsg) {
    _status = ActionStatus::ERROR;
    this->_errorMsg = errorMsg;
}

const std::string& BaseAction::getErrorMsg() const {
    return _errorMsg;
}


