-- Create Control
editChat = CUIEditBox()

-- Register Control
IDD_CHAT:regControl("IDC_EDIT_BOX_CHAT", editChat)

-- Register Event
IDD_CHAT:regControlEvent("IDC_EDIT_BOX_CHAT","IDD_CHAT_OnEditChat",1537)

-- Event Func
function IDD_CHAT_OnEditChat()
	SendChat(ws2s(editChat:GetText()))
	editChat:SetText(L"")
	--MessageBox(editChat:GetText(),0)
end