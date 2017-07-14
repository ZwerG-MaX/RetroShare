import QtQuick 2.0
import QtQuick.Controls 2.0


ToolButton
{
	height: icon.height + 5

	property alias iconUrl: icon.source
	property alias innerText: innerText.text


	Image
	{
		id: icon

		height: innerText.contentHeight
		width: innerText.contentHeight

		fillMode: Image.PreserveAspectFit
		anchors.left: parent.left
		anchors.leftMargin: 4
		anchors.verticalCenter: parent.verticalCenter
	}

	Text
	{
		id: innerText
		wrapMode: Text.WrapAnywhere
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: icon.right
		anchors.leftMargin: 5
	}


}