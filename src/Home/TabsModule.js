var ReactDOM = require('react-dom');
var React = require('react');

var TabsModule = function(props) {
    if (props.show) {
        return React.createElement('div', null,
            'Here\'s the message from the owner: ' + props.message
        );
    } else {
        return null;
    }
};

module.exports = TabsModule;